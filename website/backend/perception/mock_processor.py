import math
import random
from config_loader import CONFIG

class MockPerceptionProcessor:
    def __init__(self):
        self.t = 0.0

    def generate_point_clouds(self):
        self.t += 0.05
        cloud_count = CONFIG['simulation']['point_cloud_count']
        return [self._generate_point_cloud(index) for index in range(cloud_count)]

    def _generate_point_cloud(self, sensor_index):
        points = []
        
        # Ground (Class 0)
        for _ in range(1500):
            x = random.uniform(-30, 30)
            y = random.uniform(-30, 30)
            z = random.uniform(-0.1, 0.1)
            points.extend([round(x, 2), round(y, 2), round(z, 2), 0])
            
        # Raised Land (Class 1)
        for _ in range(300):
            x = random.uniform(10, 25)
            y = random.uniform(5, 20)
            z = random.uniform(0.5, 2.0)
            points.extend([round(x, 2), round(y, 2), round(z, 2), 1])
            
        # Potholes (Class 2)
        for _ in range(200):
            x = random.uniform(-10, -5)
            y = random.uniform(10, 15)
            z = random.uniform(-1.0, -0.3)
            points.extend([round(x, 2), round(y, 2), round(z, 2), 2])
            
        # Dynamic Obstacles (Class 3)
        # Moving in a circle
        ox = 15 * math.cos(self.t)
        oy = 15 * math.sin(self.t)
        for _ in range(100):
            x = ox + random.uniform(-1, 1)
            y = oy + random.uniform(-1, 1)
            z = random.uniform(0, 1.8)
            points.extend([round(x, 2), round(y, 2), round(z, 2), 3])
            
        # Another moving obstacle
        ox2 = -10 + 5 * math.sin(self.t * 1.5)
        oy2 = -10 + 5 * math.cos(self.t * 1.5)
        for _ in range(100):
            x = ox2 + random.uniform(-1, 1)
            y = oy2 + random.uniform(-1, 1)
            z = random.uniform(0, 1.5)
            points.extend([round(x, 2), round(y, 2), round(z, 2), 3])

        angle = sensor_index * math.pi / 2
        offset_x = (sensor_index % 2) * 0.5 - 0.25
        offset_y = (sensor_index // 2) * 0.5 - 0.25
        cos_angle = math.cos(angle)
        sin_angle = math.sin(angle)
        for index in range(0, len(points), 4):
            x, y = points[index], points[index + 1]
            points[index] = round(x * cos_angle - y * sin_angle + offset_x, 2)
            points[index + 1] = round(x * sin_angle + y * cos_angle + offset_y, 2)

        return points

    def generate_metrics(self):
        fps = random.uniform(
            CONFIG['simulation']['fps_min'],
            CONFIG['simulation']['fps_max'],
        )
        people_detected = CONFIG['simulation']['people_detected']
        return {
            "fps": round(fps, 1),
            "obstacles": people_detected,
            "obstacle_types": {"Person": people_detected}
        }
