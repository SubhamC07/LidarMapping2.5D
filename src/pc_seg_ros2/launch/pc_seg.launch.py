from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("input_topic", default_value="/velodyne_points"),
        DeclareLaunchArgument("cfg_file", default_value="randlanet_semantickitti.yml"),
        DeclareLaunchArgument("ckpt_path", default_value="randlanet_semantickitti.pth"),
        DeclareLaunchArgument("voxel_size", default_value="0.15"),

        Node(
            package="pc_seg_ros2",
            executable="seg_infer_node",
            name="seg_infer_node",
            output="screen",
            parameters=[{
                "input_topic": LaunchConfiguration("input_topic"),
                "cfg_file": LaunchConfiguration("cfg_file"),
                "ckpt_path": LaunchConfiguration("ckpt_path"),
                "voxel_size": LaunchConfiguration("voxel_size"),
            }],
        ),
        Node(
            package="pc_seg_ros2",
            executable="cluster_bbox_node",
            name="cluster_bbox_node",
            output="screen",
        ),
    ])