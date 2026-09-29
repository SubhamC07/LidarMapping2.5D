import os
from glob import glob
from setuptools import setup

package_name = "pc_seg_ros2"

setup(
    name=package_name,
    version="0.1.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), glob("launch/*.launch.py")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="Subham Chhotaray",
    maintainer_email="subhamchhotaray2006@gmail.com",
    description="CPU-only point cloud semantic segmentation (terrain/static/moving) + bbox clustering",
    license="MIT",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "seg_infer_node = pc_seg_ros2.seg_infer_node:main",
            "cluster_bbox_node = pc_seg_ros2.cluster_bbox_node:main",
            "terrain_analysis = pc_seg_ros2.terrain_analysis:main",
        ],
    },
)