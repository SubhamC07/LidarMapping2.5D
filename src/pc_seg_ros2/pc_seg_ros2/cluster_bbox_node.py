#!/usr/bin/env python3
"""
cluster_bbox_node.py
---------------------
Subscribes  : /segmented_points  (sensor_msgs/PointCloud2, rgb-colored by class)
              /point_labels      (std_msgs/Int32MultiArray, same order as cloud)
Publishes   : /obstacles          (vision_msgs/Detection3DArray)
              /obstacle_markers   (visualization_msgs/MarkerArray, for RViz2)

Terrain points are dropped. STATIC and MOVING points are clustered
per-class with DBSCAN, and each cluster gets an oriented bounding box.
"""

import numpy as np
import open3d as o3d

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2
from std_msgs.msg import Int32MultiArray
from geometry_msgs.msg import Pose, Point, Vector3
from vision_msgs.msg import Detection3D, Detection3DArray, ObjectHypothesisWithPose
from visualization_msgs.msg import Marker, MarkerArray

from .label_map import STATIC, MOVING

DBSCAN_EPS = 0.5          # meters, tune to your object spacing
DBSCAN_MIN_POINTS = 8
MIN_CLUSTER_SIZE = 10


class ClusterBBoxNode(Node):
    def __init__(self):
        super().__init__("cluster_bbox_node")
        self._latest_labels = None

        self.create_subscription(Int32MultiArray, "/point_labels", self.cb_labels, 5)
        self.create_subscription(PointCloud2, "/segmented_points", self.cb_cloud, 5)

        self.pub_det = self.create_publisher(Detection3DArray, "/obstacles", 5)
        self.pub_markers = self.create_publisher(MarkerArray, "/obstacle_markers", 5)

    def cb_labels(self, msg: Int32MultiArray):
        self._latest_labels = np.array(msg.data, dtype=np.int32)

    def cb_cloud(self, msg: PointCloud2):
        if self._latest_labels is None:
            return
        pts = np.array(
            list(point_cloud2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True)),
            dtype=np.float32,
        )
        labels = self._latest_labels
        if pts.shape[0] != labels.shape[0]:
            self.get_logger().warn("Point/label count mismatch, skipping frame")
            return

        det_array = Detection3DArray()
        det_array.header = msg.header
        marker_array = MarkerArray()
        marker_id = 0

        for class_id, class_name in ((STATIC, "static_obstacle"), (MOVING, "moving_object")):
            mask = labels == class_id
            class_pts = pts[mask]
            if class_pts.shape[0] < MIN_CLUSTER_SIZE:
                continue

            pcd = o3d.geometry.PointCloud()
            pcd.points = o3d.utility.Vector3dVector(class_pts)
            cluster_ids = np.array(
                pcd.cluster_dbscan(eps=DBSCAN_EPS, min_points=DBSCAN_MIN_POINTS)
            )

            for cid in set(cluster_ids.tolist()):
                if cid < 0:
                    continue  # noise
                cluster_pts = class_pts[cluster_ids == cid]
                if cluster_pts.shape[0] < MIN_CLUSTER_SIZE:
                    continue

                cluster_pcd = o3d.geometry.PointCloud()
                cluster_pcd.points = o3d.utility.Vector3dVector(cluster_pts)
                obb = cluster_pcd.get_oriented_bounding_box()

                det_array.detections.append(self._to_detection3d(obb, class_name, msg.header))
                marker_array.markers.append(
                    self._to_marker(obb, class_name, marker_id, msg.header)
                )
                marker_id += 1

        self.pub_det.publish(det_array)
        self.pub_markers.publish(marker_array)

    @staticmethod
    def _to_detection3d(obb, class_name, header) -> Detection3D:
        det = Detection3D()
        det.header = header
        hyp = ObjectHypothesisWithPose()
        hyp.hypothesis.class_id = class_name
        hyp.hypothesis.score = 1.0
        det.results.append(hyp)

        center = obb.center
        extent = obb.extent
        det.bbox.center.position = Point(x=float(center[0]), y=float(center[1]), z=float(center[2]))
        det.bbox.size = Vector3(x=float(extent[0]), y=float(extent[1]), z=float(extent[2]))
        return det

    @staticmethod
    def _to_marker(obb, class_name, marker_id, header) -> Marker:
        m = Marker()
        m.header = header
        m.ns = class_name
        m.id = marker_id
        m.type = Marker.CUBE
        m.action = Marker.ADD
        center = obb.center
        extent = obb.extent
        m.pose.position = Point(x=float(center[0]), y=float(center[1]), z=float(center[2]))
        m.scale = Vector3(x=float(extent[0]), y=float(extent[1]), z=float(extent[2]))
        if class_name == "moving_object":
            m.color.r, m.color.g, m.color.b, m.color.a = 1.0, 0.1, 0.1, 0.4
        else:
            m.color.r, m.color.g, m.color.b, m.color.a = 1.0, 1.0, 0.1, 0.4
        m.lifetime.sec = 1
        return m


def main():
    rclpy.init()
    node = ClusterBBoxNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()