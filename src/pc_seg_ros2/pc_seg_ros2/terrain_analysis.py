#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs_py import point_cloud2
import std_msgs.msg
import open3d as o3d
import numpy as np


class AdvancedTerrainAnalyzer(Node):
    def __init__(self):
        super().__init__('advanced_terrain_analyzer')

        # Declare ROS 2 parameters
        self.declare_parameter('input_topic', '/velodyne_points')
        self.declare_parameter('grid_resolution', 0.1)  # 10cm grid cells
        self.declare_parameter('pothole_depth', 0.05)   # 5cm below ground
        self.declare_parameter('bump_height', 0.06)     # 6cm above ground
        self.declare_parameter('obstacle_height', 0.3)  # 30cm+ is an obstacle

        input_topic = self.get_parameter('input_topic').get_parameter_value().string_value
        self.res = self.get_parameter('grid_resolution').get_parameter_value().double_value
        self.pothole_thresh = self.get_parameter('pothole_depth').get_parameter_value().double_value
        self.bump_thresh = self.get_parameter('bump_height').get_parameter_value().double_value
        self.obs_thresh = self.get_parameter('obstacle_height').get_parameter_value().double_value

        # Subscriber for point cloud input
        self.subscription = self.create_subscription(
            PointCloud2,
            input_topic,
            self.pointcloud_callback,
            10
        )

        # Publishers for segmented terrain categories
        self.pub_ground = self.create_publisher(PointCloud2, 'terrain/flat_ground', 10)
        self.pub_potholes = self.create_publisher(PointCloud2, 'terrain/potholes', 10)
        self.pub_bumps = self.create_publisher(PointCloud2, 'terrain/raised_land', 10)
        self.pub_obstacles = self.create_publisher(PointCloud2, 'terrain/obstacles', 10)

        self.get_logger().info(f"Subscribed to '{input_topic}' and processing terrain in real-time...")

    def pointcloud_callback(self, msg: PointCloud2):
        # Read x, y, z points from incoming PointCloud2 message
        gen = point_cloud2.read_points(msg, field_names=('x', 'y', 'z'), skip_nans=True)
        pts = np.array(list(gen), dtype=[('x', 'f4'), ('y', 'f4'), ('z', 'f4')])

        if len(pts) == 0:
            return

        # Convert structured array to standard Nx3 float array
        pts_array = np.column_stack((pts['x'], pts['y'], pts['z']))

        # Convert NumPy array to Open3D PointCloud object
        pcd = o3d.geometry.PointCloud()
        pcd.points = o3d.utility.Vector3dVector(pts_array)

        # Step 1: Global/Regional Ground Plane Estimation via RANSAC
        plane_model, inliers = pcd.segment_plane(
            distance_threshold=0.2, ransac_n=3, num_iterations=200
        )
        a, b, c, d = plane_model  # Ax + By + Cz + D = 0

        # Avoid division by zero if plane normal is completely horizontal
        if abs(c) < 1e-6:
            self.get_logger().warn("RANSAC estimated a near-vertical plane for ground. Skipping frame.")
            return

        # Calculate expected reference ground height at every point's (x, y)
        # Z_ref = (-a*X - b*Y - d) / c
        expected_z = (-a * pts_array[:, 0] - b * pts_array[:, 1] - d) / c
        height_diff = pts_array[:, 2] - expected_z  # Positive = Above ground, Negative = Below ground

        # Step 2: Feature Segmentation based on Height Thresholds
        pothole_mask = height_diff < -self.pothole_thresh
        bump_mask = (height_diff >= self.bump_thresh) & (height_diff < self.obs_thresh)
        obstacle_mask = height_diff >= self.obs_thresh
        ground_mask = (height_diff >= -self.pothole_thresh) & (height_diff < self.bump_thresh)

        # Step 3: Publish Classified Point Clouds (using original frame and timestamp)
        header = std_msgs.msg.Header()
        header.stamp = msg.header.stamp
        header.frame_id = msg.header.frame_id

        self.pub_ground.publish(self.create_pc2_msg(header, pts_array[ground_mask]))
        self.pub_potholes.publish(self.create_pc2_msg(header, pts_array[pothole_mask]))
        self.pub_bumps.publish(self.create_pc2_msg(header, pts_array[bump_mask]))
        self.pub_obstacles.publish(self.create_pc2_msg(header, pts_array[obstacle_mask]))

        self.get_logger().info(
            f"Analyzed: {np.sum(pothole_mask)} Pothole pts | "
            f"{np.sum(bump_mask)} Raised land pts | "
            f"{np.sum(obstacle_mask)} Obstacle pts | "
            f"{np.sum(ground_mask)} Ground pts"
        )

    def create_pc2_msg(self, header, points):
        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1),
        ]
        return point_cloud2.create_cloud(header, fields, points)


def main(args=None):
    rclpy.init(args=args)
    node = AdvancedTerrainAnalyzer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()