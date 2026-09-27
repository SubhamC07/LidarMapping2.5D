#!/usr/bin/env python3
"""
seg_infer_node.py
------------------
Subscribes  : /velodyne_points   (sensor_msgs/PointCloud2)
Publishes   : /segmented_points  (sensor_msgs/PointCloud2, colored by class)
              /point_labels      (std_msgs/Int32MultiArray, raw 3-class labels,
                                   same point order as /segmented_points)

Runs Open3D-ML's RandLA-Net (pretrained on SemanticKITTI) on CPU.
No ONNX / TensorRT export needed — loads the .pth checkpoint directly.
"""

import numpy as np
import torch

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs_py import point_cloud2
from std_msgs.msg import Header, Int32MultiArray

import open3d.ml as _ml3d
import open3d.ml.torch as ml3d

from .label_map import remap_to_3class, CLASS_COLOR

CFG_FILE = "randlanet_semantickitti.yml"      # ship this next to the node, or give absolute path
CKPT_PATH = "randlanet_semantickitti.pth"     # downloaded checkpoint, see README
VOXEL_SIZE = 0.15                             # tune for your CPU: bigger = faster, coarser


class SegInferNode(Node):
    def __init__(self):
        super().__init__("seg_infer_node")

        self.declare_parameter("cfg_file", CFG_FILE)
        self.declare_parameter("ckpt_path", CKPT_PATH)
        self.declare_parameter("voxel_size", VOXEL_SIZE)
        self.declare_parameter("input_topic", "/velodyne_points")

        cfg_file = self.get_parameter("cfg_file").value
        ckpt_path = self.get_parameter("ckpt_path").value
        self.voxel_size = self.get_parameter("voxel_size").value
        input_topic = self.get_parameter("input_topic").value

        self.get_logger().info("Loading RandLA-Net (CPU) ... this can take a few seconds")
        cfg = _ml3d.utils.Config.load_from_file(cfg_file)
        self.model = ml3d.models.RandLANet(**cfg.model)
        ckpt = torch.load(ckpt_path, map_location="cpu")
        state_dict = ckpt.get("model_state_dict", ckpt)
        self.model.load_state_dict(state_dict)
        self.model.eval()
        self.model.device = "cpu"
        self.get_logger().info("Model loaded on CPU.")

        self.sub = self.create_subscription(PointCloud2, input_topic, self.cb_cloud, 5)
        self.pub_cloud = self.create_publisher(PointCloud2, "/segmented_points", 5)
        self.pub_labels = self.create_publisher(Int32MultiArray, "/point_labels", 5)

    def cb_cloud(self, msg: PointCloud2):
        pts = np.array(
            list(point_cloud2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True)),
            dtype=np.float32,
        )
        if pts.shape[0] == 0:
            return

        # ---- 1. voxel downsample (CPU speed) ----
        ds_pts, ds_index = self._voxel_downsample(pts, self.voxel_size)

        # ---- 2. run RandLA-Net inference ----
        kitti_labels = self._infer(ds_pts)

        # ---- 3. remap to 3-class scheme ----
        labels_3c = remap_to_3class(kitti_labels)

        # ---- 4. publish colored cloud + raw labels ----
        self._publish_colored_cloud(msg.header, ds_pts, labels_3c)
        self.pub_labels.publish(Int32MultiArray(data=labels_3c.astype(np.int32).tolist()))

    @staticmethod
    def _voxel_downsample(pts: np.ndarray, voxel_size: float):
        import open3d as o3d
        pcd = o3d.geometry.PointCloud()
        pcd.points = o3d.utility.Vector3dVector(pts)
        down = pcd.voxel_down_sample(voxel_size)
        return np.asarray(down.points, dtype=np.float32), None

    def _infer(self, points_xyz: np.ndarray) -> np.ndarray:
        """Runs Open3D-ML's streaming inference API (no Dataset object needed)."""
        data = {
            "point": points_xyz,
            "feat": None,
            "label": np.zeros((points_xyz.shape[0],), dtype=np.int32),
        }
        self.model.inference_begin(data)
        with torch.no_grad():
            while True:
                inputs = self.model.inference_preprocess()
                results = self.model(inputs)
                if self.model.inference_end(inputs, results):
                    break
        return self.model.inference_result["predict_labels"]

    def _publish_colored_cloud(self, header: Header, pts: np.ndarray, labels: np.ndarray):
        fields = [
            PointField(name="x", offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name="y", offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name="z", offset=8, datatype=PointField.FLOAT32, count=1),
            PointField(name="rgb", offset=12, datatype=PointField.FLOAT32, count=1),
        ]
        cloud_data = []
        for (x, y, z), lbl in zip(pts, labels):
            r, g, b = CLASS_COLOR.get(int(lbl), (255, 255, 255))
            rgb_packed = (int(r) << 16) | (int(g) << 8) | int(b)
            rgb_float = np.frombuffer(np.uint32(rgb_packed).tobytes(), dtype=np.float32)[0]
            cloud_data.append([x, y, z, rgb_float])
        out_msg = point_cloud2.create_cloud(header, fields, cloud_data)
        self.pub_cloud.publish(out_msg)


def main():
    rclpy.init()
    node = SegInferNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()