import random
import math
from config_loader import CONFIG

class MockGridMapper:
    def __init__(self):
        self.resolutions = CONFIG['map']['resolutions']
        self.ranges = CONFIG['map']['ranges']
        self.t = 0.0

    def generate_grid(self):
        self.t += 0.05
        cells = []
        
        # Helper to generate a cell [x, y, size, elevation, class]
        
        # Near Zone (High Res)
        near_res = self.resolutions['near']
        near_range = self.ranges['near_max']
        steps_near = int(near_range / near_res)
        
        # To avoid sending too much data, we only send a sparse subset of occupied/interesting cells
        
        # Generate some flat ground in near zone
        for _ in range(200):
            x = random.randint(-100, 100) * near_res
            y = random.randint(-100, 100) * near_res
            cells.extend([round(x, 2), round(y, 2), near_res, 0.0, 0])
            
        # Potholes in near zone
        for _ in range(50):
            x = -7 + random.uniform(-2, 2)
            y = 12 + random.uniform(-2, 2)
            # snap to grid
            x = round(x / near_res) * near_res
            y = round(y / near_res) * near_res
            cells.extend([round(x, 2), round(y, 2), near_res, -0.5, 2])
            
        # Middle Zone (Medium Res)
        mid_res = self.resolutions['middle']
        for _ in range(100):
            # random positions between near and middle max
            angle = random.uniform(0, 2 * math.pi)
            dist = random.uniform(near_range, self.ranges['middle_max'])
            x = math.cos(angle) * dist
            y = math.sin(angle) * dist
            x = round(x / mid_res) * mid_res
            y = round(y / mid_res) * mid_res
            cells.extend([round(x, 2), round(y, 2), mid_res, 1.0, 1]) # Raised land

        # Moving obstacle in grid
        ox = 15 * math.cos(self.t)
        oy = 15 * math.sin(self.t)
        ox = round(ox / near_res) * near_res
        oy = round(oy / near_res) * near_res
        cells.extend([round(ox, 2), round(oy, 2), near_res, 1.5, 3])
        
        ox2 = -10 + 5 * math.sin(self.t * 1.5)
        oy2 = -10 + 5 * math.cos(self.t * 1.5)
        ox2 = round(ox2 / near_res) * near_res
        oy2 = round(oy2 / near_res) * near_res
        cells.extend([round(ox2, 2), round(oy2, 2), near_res, 1.2, 3])

        return cells
