import math
import os
import threading


class RosSubscriber:
    max_points_per_cloud = 10000

    def __init__(self, pointcloud_topics, grid_topic, domain_id):
        self.pointcloud_topics = pointcloud_topics
        self.grid_topic = grid_topic
        self.domain_id = domain_id
        self._point_clouds = [[] for _ in pointcloud_topics]
        self._grid_map = None
        self._lock = threading.Lock()
        self._rclpy = None
        self._node = None
        self._executor = None
        self._thread = None

    def start(self):
        try:
            import rclpy
            from grid_map_msgs.msg import GridMap
            from rclpy.executors import ExternalShutdownException, SingleThreadedExecutor
            from rclpy.node import Node
            from rclpy.qos import qos_profile_sensor_data
            from sensor_msgs.msg import PointCloud2
            from sensor_msgs_py import point_cloud2
        except ImportError as error:
            raise RuntimeError(
                "ROS 2 Python packages are unavailable. Source the ROS setup file "
                "before starting the backend."
            ) from error

        if not rclpy.ok():
            os.environ["ROS_DOMAIN_ID"] = str(self.domain_id)
            rclpy.init()

        self._rclpy = rclpy
        self._node = Node("lidar_mapping_dashboard")
        for index, topic_config in enumerate(self.pointcloud_topics):
            self._node.create_subscription(
                PointCloud2,
                topic_config["topic"],
                self._cloud_callback(index, point_cloud2),
                qos_profile_sensor_data,
            )
            self._node.get_logger().info(
                f"Subscribed to {topic_config['topic']} ({topic_config['name']})"
            )

        self._node.create_subscription(
            GridMap,
            self.grid_topic,
            self._grid_map_callback,
            qos_profile_sensor_data,
        )
        self._node.get_logger().info(f"Subscribed to grid map {self.grid_topic}")

        self._executor = SingleThreadedExecutor()
        self._executor.add_node(self._node)
        self._thread = threading.Thread(
            target=self._spin,
            args=(ExternalShutdownException,),
            daemon=True,
        )
        self._thread.start()

    def _spin(self, external_shutdown_exception):
        try:
            self._executor.spin()
        except external_shutdown_exception:
            pass

    def _cloud_callback(self, index, point_cloud2):
        def receive(message):
            values = point_cloud2.read_points(
                message,
                field_names=["x", "y", "z"],
                skip_nans=True,
            )
            stride = max(1, math.ceil(len(values) / self.max_points_per_cloud))
            points = []
            for value in values[::stride]:
                x = float(value["x"])
                y = float(value["y"])
                z = float(value["z"])
                if all(math.isfinite(component) for component in (x, y, z)):
                    points.extend((x, y, z, index))

            with self._lock:
                self._point_clouds[index] = points

        return receive

    def _grid_map_callback(self, message):
        if not message.layers or not message.data:
            return

        layer_index = next(
            (index for index, name in enumerate(message.layers) if name.lower() == "elevation"),
            None,
        )
        if layer_index is None:
            layer_index = next(
                (
                    index
                    for index, name in enumerate(message.layers)
                    if not any(term in name.lower() for term in ("class", "label", "semantic"))
                ),
                None,
            )
        if layer_index is None:
            return

        layer = message.data[layer_index]
        dimensions = layer.layout.dim
        if len(dimensions) < 2:
            return

        rows = dimensions[0].size
        columns = dimensions[1].size
        raw_values = layer.data
        data_offset = layer.layout.data_offset
        if not rows or not columns or len(raw_values) < data_offset + rows * columns:
            return

        values = []
        for row in range(rows):
            source_row = (row + message.outer_start_index) % rows
            for column in range(columns):
                source_column = (column + message.inner_start_index) % columns
                value = float(raw_values[data_offset + source_row * columns + source_column])
                values.append(value if math.isfinite(value) else None)

        grid_map = {
            "width": columns,
            "height": rows,
            "resolution": message.info.resolution,
            "length_x": message.info.length_x,
            "length_y": message.info.length_y,
            "layer": message.layers[layer_index],
            "values": values,
        }
        with self._lock:
            self._grid_map = grid_map

    def get_point_clouds(self):
        with self._lock:
            return [points.copy() for points in self._point_clouds]

    def get_grid_map(self):
        with self._lock:
            return self._grid_map

    def stop(self):
        if self._executor is not None:
            self._executor.shutdown(timeout_sec=2)
        if self._node is not None:
            self._node.destroy_node()
        if self._rclpy is not None and self._rclpy.ok():
            self._rclpy.shutdown()
        if self._thread is not None:
            self._thread.join(timeout=2)