#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import xacro
from ament_index_python.packages import get_package_share_directory, get_package_prefix
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable, TimerAction, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node


def generate_launch_description():
    # Package details
    pkg_name = 'lid_description'
    pkg_person_share = get_package_share_directory(pkg_name)
    pkg_person_prefix = get_package_prefix(pkg_name)
    sim_pkg_share = get_package_share_directory('lid_simulation')

    # 1) Declare use_sim_time arg
    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time', default_value='True',
        description='Use simulation (Gazebo) clock'
    )

    # 2) Set Ignition/Gazebo resource & plugin paths for the local package.
    resource_root = os.path.dirname(pkg_person_share)
    ign_res = os.pathsep.join(filter(None, [
        os.environ.get('IGN_GAZEBO_RESOURCE_PATH', ''),
        os.environ.get('GZ_SIM_RESOURCE_PATH', ''),
        resource_root,
        pkg_person_share,
        os.path.join(pkg_person_share, 'models')
    ]))
    ign_plg = os.pathsep.join(filter(None, [
        os.environ.get('IGN_GAZEBO_SYSTEM_PLUGIN_PATH', ''),
        os.environ.get('IGN_GAZEBO_PLUGIN_PATH', ''),
        os.environ.get('GZ_SIM_SYSTEM_PLUGIN_PATH', ''),
        os.environ.get('GZ_SIM_PLUGIN_PATH', ''),
        os.path.join(pkg_person_prefix, 'lib')
    ]))

    # 3) Process the person_description.xacro with proper namespacing
    xacro_file = os.path.join(pkg_person_share, 'models', 'ebot', 'person.urdf.xacro')
    robot_desc = xacro.process_file(xacro_file, mappings={'prefix': 'person_'}).toxml()

    # Export the resource and plugin paths before starting Gazebo.
    launch_description = [
        SetEnvironmentVariable('IGN_GAZEBO_RESOURCE_PATH', ign_res),
        SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', ign_res),
        SetEnvironmentVariable('IGN_GAZEBO_SYSTEM_PLUGIN_PATH', ign_plg),
        SetEnvironmentVariable('IGN_GAZEBO_PLUGIN_PATH', ign_plg),
        SetEnvironmentVariable('GZ_SIM_SYSTEM_PLUGIN_PATH', ign_plg),
        SetEnvironmentVariable('GZ_SIM_PLUGIN_PATH', ign_plg),
    ]

    # 4) Robot State Publisher with person namespace
    rsp_node = Node(
        package='robot_state_publisher', 
        executable='robot_state_publisher',
        name='person_state_publisher', 
        namespace='person',
        output='screen',
        remappings=[
            ('tf', '/tf'),
            ('tf_static', '/tf_static'),
            ('joint_states', '/joint_states_person'),
        ],
        parameters=[{
            'use_sim_time': LaunchConfiguration('use_sim_time'),
            'robot_description': robot_desc,
            # 'frame_prefix': 'person_'
        }]
    )

    # 5) Spawn the person after a short delay with namespace
    spawn_person = TimerAction(
        period=2.0,
        actions=[
            Node(
                package='ros_gz_sim', 
                executable='create', 
                name='spawn_person',
                output='screen',
                arguments=[
                    '-name', 'person', 
                    '-topic', '/person/robot_description',
                    '-x', '-1.5339', 
                    '-y', '-4.6156', 
                    '-z', '0.0550', 
                    '-Y', '1.57'
                ],
            )
        ]
    )

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        name='person_bridge',
        parameters=[{
            'config_file': os.path.join(sim_pkg_share, 'config', 'bridge.yaml'),
            'use_sim_time': True,
        }],
        output='screen'
    )

    # camera_info_relay = TimerAction(
    #     period=15.0,
    #     actions=[
    #         Node(
    #             package='topic_tools',
    #             executable='relay',
    #             name='camera_info_relay',
    #             # namespace='ur5',
    #             arguments=['/camera/camera_info', '/camera/depth/camera_info'],
    #             output='screen',
    #             parameters=[{"use_sim_time": True}],
    #         )
    #     ]
    # )

    # Assemble launch description
    return LaunchDescription([
        *launch_description,
        use_sim_time_arg,
        # bridge,
        rsp_node,
        spawn_person,
        # camera_info_relay
    ])