#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data

# Message Imports
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2
from grid_map_msgs.msg import GridMap

import numpy as np
import matplotlib.pyplot as plt
import sys
import time

class MemoryUsageComparator(Node):
    def __init__(self):
        super().__init__('memory_usage_comparator')

        # 1. Raw 3D LiDAR subscription
        self.pc_sub = self.create_subscription(
            PointCloud2,
            '/velodyne_points',
            self.pc_callback,
            qos_profile_sensor_data
        )

        # 2. FastDEM 2.5D GridMap subscription
        self.gridmap_sub = self.create_subscription(
            GridMap,
            '/fastdem/postprocess/gridmap',  # Adjust to your FastDEM GridMap topic name
            self.gridmap_callback,
            qos_profile_sensor_data
        )

        # Storage & Performance Tracking
        self.raw_pc_bytes = 0
        self.raw_pc_points = 0
        
        self.gridmap_bytes = 0
        self.grid_matrix = None
        self.grid_info = {}

        # Setup GUI Plot
        plt.ion()
        self.fig, (self.ax_map, self.ax_bar) = plt.subplots(1, 2, figsize=(14, 6))
        self.fig.canvas.manager.set_window_title('Memory Comparator Chart')

        self.create_timer(0.2, self.update_plot)
        self.get_logger().info("FastDEM GridMap Memory Comparator initialized.")

    def pc_callback(self, msg: PointCloud2):
        # Read payload byte size directly from raw ROS message data buffer
        self.raw_pc_bytes = len(msg.data)
        
        try:
            # Standard read_points generator (compatible with ROS 2 Humble)
            pts_gen = point_cloud2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True)
            pts_list = list(pts_gen)
            self.raw_pc_points = len(pts_list)
        except Exception as e:
            self.get_logger().error(f"PointCloud parsing error: {e}")

    def gridmap_callback(self, msg: GridMap):
        # Compute serialized RAM footprint of message payload
        self.gridmap_bytes = sys.getsizeof(msg)
        for data_array in msg.data:
            self.gridmap_bytes += sys.getsizeof(data_array.data)

        res = msg.info.resolution
        length_x = msg.info.length_x
        length_y = msg.info.length_y
        
        if "elevation" in msg.layers:
            idx = msg.layers.index("elevation")
            data_flat = msg.data[idx].data
            
            cols = int(round(length_x / res))
            rows = int(round(length_y / res))
            
            if len(data_flat) == rows * cols:
                # Fortran order ('F') properly aligns ROS 2 GridMap column-major storage
                grid = np.array(data_flat, dtype=np.float32).reshape((rows, cols), order='F')
                grid = np.nan_to_num(grid, nan=0.0)
                self.grid_matrix = grid
                self.grid_info = {'res': res, 'rows': rows, 'cols': cols}
                
    def update_plot(self):
        if self.grid_matrix is None or self.raw_pc_bytes == 0:
            return

        # -------------------------------------------------------------
        # Panel 1: 2.5D GridMap Elevation Heatmap Visualization
        # -------------------------------------------------------------
        self.ax_map.clear()
        im = self.ax_map.imshow(
            self.grid_matrix, 
            cmap='terrain', 
            origin='lower'
        )
        self.ax_map.set_title(
            f"FastDEM 2.5D GridMap ({self.grid_info['rows']}x{self.grid_info['cols']} cells @ {self.grid_info['res']}m)"
        )
        self.ax_map.set_xlabel("Grid X (Cells)")
        self.ax_map.set_ylabel("Grid Y (Cells)")

        # -------------------------------------------------------------
        # Panel 2: Memory Footprint (KB) Comparison
        # -------------------------------------------------------------
        self.ax_bar.clear()
        
        raw_kb = self.raw_pc_bytes / 1024.0
        grid_kb = self.gridmap_bytes / 1024.0

        categories = ['Raw 3D PointCloud\n(/velodyne_points)', '2.5D GridMap\n(FastDEM)']
        memory_values = [raw_kb, grid_kb]
        colors = ['#e74c3c', '#2ecc71']

        bars = self.ax_bar.bar(categories, memory_values, color=colors, width=0.4)
        self.ax_bar.set_ylabel('Memory Footprint (Kilobytes - KB)')
        self.ax_bar.set_title('Real-time RAM Usage Reduction')

        # Add KB values on top of bars
        for bar in bars:
            yval = bar.get_height()
            self.ax_bar.text(
                bar.get_x() + bar.get_width()/2.0, 
                yval + (max(memory_values) * 0.02), 
                f'{yval:.1f} KB', 
                ha='center', va='bottom', fontweight='bold'
            )

        # Show relative memory reduction percentage
        if raw_kb > 0:
            savings = ((raw_kb - grid_kb) / raw_kb) * 100.0
            self.ax_bar.text(
                0.5, 0.85, 
                f'RAM Reduction: {savings:.1f}%', 
                transform=self.ax_bar.transAxes, 
                ha='center', fontsize=12, fontweight='bold',
                bbox=dict(boxstyle='round', facecolor='yellow', alpha=0.6)
            )

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()

def main(args=None):
    rclpy.init(args=args)
    node = MemoryUsageComparator()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()