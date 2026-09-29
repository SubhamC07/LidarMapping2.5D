from setuptools import find_packages
from setuptools import setup

setup(
    name='jsk_recognition_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('jsk_recognition_msgs', 'jsk_recognition_msgs.*')),
)
