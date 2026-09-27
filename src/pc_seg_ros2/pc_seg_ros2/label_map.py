"""
Maps SemanticKITTI's fine-grained class IDs down to 3 super-classes:
  0 = terrain, 1 = static obstacle, 2 = moving object, 255 = ignore

SemanticKITTI label IDs (standard config, see semantic-kitti-api repo's
config/semantic-kitti.yaml for the authoritative list). Adjust the sets
below if the checkpoint you load uses a different label remap.
"""

TERRAIN_IDS = {
    40,   # road
    44,   # parking
    48,   # sidewalk
    49,   # other-ground
    72,   # terrain
    70,   # vegetation (ground-level foliage, optional: move to static if you
          # want trees treated as obstacles instead of terrain)
}

MOVING_IDS = {
    252,  # moving-car
    253,  # moving-bicyclist
    254,  # moving-person
    255,  # moving-motorcyclist
    256,  # moving-on-rails
    257,  # moving-bus
    258,  # moving-truck
    259,  # moving-other-vehicle
}

IGNORE_IDS = {0, 1}  # unlabeled, outlier

# everything else (buildings, poles, fences, parked vehicles, static
# pedestrians, signs, trunks, etc.) falls through to STATIC by default.

TERRAIN, STATIC, MOVING, IGNORE = 0, 1, 2, 255


def remap_to_3class(kitti_label_array):
    """kitti_label_array: np.ndarray[int] of raw SemanticKITTI ids.
    Returns np.ndarray[int] with values {0,1,2,255}."""
    import numpy as np
    out = np.full(kitti_label_array.shape, STATIC, dtype=np.uint8)
    for tid in TERRAIN_IDS:
        out[kitti_label_array == tid] = TERRAIN
    for mid in MOVING_IDS:
        out[kitti_label_array == mid] = MOVING
    for iid in IGNORE_IDS:
        out[kitti_label_array == iid] = IGNORE
    return out


# RGB colors for visualization (RViz2 / colored PointCloud2)
CLASS_COLOR = {
    TERRAIN: (80, 200, 80),     # green
    STATIC:  (200, 200, 30),    # yellow
    MOVING:  (230, 30, 30),     # red
    IGNORE:  (100, 100, 100),   # gray
}