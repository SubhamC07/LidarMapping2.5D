import yaml
from pathlib import Path

def load_config():
    config_dir = Path(__file__).parent.parent / "config"
    with open(config_dir / "system.yaml", 'r') as config_file:
        config = yaml.safe_load(config_file)
    with open(config_dir / "ros_topics.yaml", 'r') as topics_file:
        topics_config = yaml.safe_load(topics_file)
    config["ros"] = topics_config["ros"]
    return config

CONFIG = load_config()
