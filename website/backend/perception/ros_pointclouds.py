import threading


class RosPointCloudSubscriber:
    def __init__(self, topics, domain_id):
        self.topics = topics
        self.domain_id = domain_id
        self._point_clouds = [[] for _ in topics]
        self._lock = threading.Lock()
        self._rclpy = None
        self._node = None
        self._executor = None
        self._thread = None

    def start(self):
        try:
            import rclpy
            from rclpy.executors import SingleThreadedExecutor
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
            rclpy.init(args=["--ros-domain-id", str(self.domain_id)])

        self._rclpy = rclpy
        self._node = Node("lidar_mapping_dashboard")
        for index, topic_config in enumerate(self.topics):
            self._node.create_subscription(
                PointCloud2,
                topic_config["topic"],
                self._cloud_callback(index, point_cloud2),
                qos_profile_sensor_data,
            )
            self._node.get_logger().info(
                f"Subscribed to {topic_config['topic']} ({topic_config['name']})"
            )

        self._executor = SingleThreadedExecutor()
        self._executor.add_node(self._node)
        self._thread = threading.Thread(target=self._executor.spin, daemon=True)
        self._thread.start()

    def _cloud_callback(self, index, point_cloud2):
        def receive(message):
            values = point_cloud2.read_points(
                message,
                field_names=["x", "y", "z"],
                skip_nans=True,
            )
            points = []
            for value in values:
                x = float(value["x"])
                y = float(value["y"])
                z = float(value["z"])
                points.extend((x, y, z, index))

            with self._lock:
                self._point_clouds[index] = points

        return receive

    def get_point_clouds(self):
        with self._lock:
            return [points.copy() for points in self._point_clouds]

    def stop(self):
        if self._executor is not None:
            self._executor.shutdown()
        if self._node is not None:
            self._node.destroy_node()
        if self._rclpy is not None and self._rclpy.ok():
            self._rclpy.shutdown()
        if self._thread is not None:
            self._thread.join(timeout=2)