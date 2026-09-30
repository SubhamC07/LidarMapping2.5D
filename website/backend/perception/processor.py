import random
from config_loader import CONFIG


class PerceptionProcessor:
    def generate_metrics(self):
        fps = random.uniform(
            CONFIG['simulation']['fps_min'],
            CONFIG['simulation']['fps_max'],
        )
        people_detected = CONFIG['simulation']['people_detected']
        return {
            "fps": round(fps, 1),
            "obstacles": people_detected,
            "obstacle_types": {"Person": people_detected},
        }