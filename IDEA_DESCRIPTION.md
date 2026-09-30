# SteelWings: Foveated Semantic 2.5D LiDAR Mapping

## Idea Description

### At a glance

SteelWings is a ROS 2 mapping and perception system for autonomous ground vehicles. It aims to turn dense LiDAR scans into a compact, useful view of the world: detailed where the vehicle must make immediate safety decisions, and progressively simpler farther away. Each mapped cell should carry more than height. The intended map combines elevation, terrain traversability, obstacle semantics, confidence, and, where supported, motion information. A live dashboard makes the resulting map and its performance inspectable.

The project is motivated by a practical trade-off. A full 3D point cloud preserves rich geometry but can be expensive to process and retain. A conventional 2D occupancy map is lighter, but discards height differences that matter for curbs, bumps, potholes, and overhanging or raised obstacles. A 2.5D elevation map keeps a compact height summary for each horizontal location. Foveated resolution extends that idea: use small cells nearby and larger cells farther out, instead of paying the same cost everywhere.

### Problem

An autonomous vehicle needs enough geometric detail to detect hazards and choose a safe path, but it must make those decisions under real-time limits on compute, memory, and communication. Uniformly processing a dense 3D scan can spend resources on distant detail that has little immediate value. A single-resolution 2D grid has the opposite weakness: it is efficient, but can hide important vertical structure.

The goal is therefore not simply to downsample a point cloud. It is to preserve the right information at the right distance, align cells consistently as the vehicle moves, and carry terrain and object meaning into a map that can be used by navigation and understood by an operator.

### Proposed solution

The proposed pipeline receives LiDAR `PointCloud2` messages, filters and classifies the points, and projects them into a distance-aware 2.5D representation. Close to the sensor, fine cells preserve detail for immediate collision avoidance and terrain assessment. In outer bands, progressively larger cells summarize the scene while retaining features relevant to route planning.

As a concrete starting target, the project statement suggests 5 cm cells within 10 m and cells approaching 50 cm out to 100 m. Those values are design targets, not current FastDEM runtime settings. They should be configurable and validated against the sensor, vehicle speed, and compute platform.

For each cell, the intended map can store:

- Elevation estimate, plus minimum and maximum observed height where useful.
- Terrain class, such as drivable ground, raised terrain, pothole, or unknown.
- Object class, such as static obstacle or moving object.
- Confidence or uncertainty, point count, and observation age.
- Optional traversability or occupancy score derived from height variation and semantic evidence.

This representation is meant to support both planning and visualization. It is not a replacement for a full 3D point cloud in every task; it is a compact navigation-facing summary, with selected raw or segmented points retained when they are needed for inspection or downstream perception.

## How the repository currently fits the idea

The repository contains several useful building blocks. They are not yet one fully integrated foveated semantic-mapping pipeline, so this description separates working code from the intended next step.

### Mapping foundation: FastDEM

FastDEM converts point clouds into an elevation grid and maintains useful per-cell information. The point-cloud conversion code groups points by grid index and computes statistics such as minimum and maximum height, mean, variance, point count, intensity, and color. Its live mapping path uses configurable height estimation, including Kalman and P² quantile estimators, and supports local maps that follow the robot as well as global maps with a fixed origin. Raycasting and post-processing features such as inpainting, uncertainty fusion, and feature extraction are also available in the mapping code and configuration.

The ROS 2 node reads scans from `/velodyne_points` by default and publishes its map as `/fastdem/mapping/gridmap`, along with point-cloud and visualization outputs. The default local configuration uses a 15 m by 15 m map at 0.1 m resolution and a 20 m range filter. The global configuration also uses one 0.1 m resolution, over a larger configured map. These are regular, single-resolution grids: the current FastDEM map does not increase cell size with distance.

### Point-cloud segmentation and object proposals

The `pc_seg_ros2` package includes a RandLA-Net inference node using Open3D-ML and a SemanticKITTI-pretrained checkpoint. It subscribes to `/velodyne_points`, voxel-downsamples the scan (default 0.15 m), runs inference on the CPU, and remaps model labels into terrain, static-obstacle, moving-object, and ignored categories. It publishes a colored cloud on `/segmented_points` and labels on `/point_labels`.

A companion node clusters static and moving points with DBSCAN and publishes 3D detections and RViz markers on `/obstacles` and `/obstacle_markers`. This is a useful object-proposal path, but the current code does not perform temporal tracking. A moving-class label is not, by itself, proof that an object is moving in the current scene; robust motion decisions need frame-to-frame association or another temporal method.

There is also a separate terrain-analysis node. It estimates a plane with RANSAC and applies height thresholds to publish `/terrain/flat_ground`, `/terrain/raised_land`, `/terrain/potholes`, and `/terrain/obstacles`. This is a heuristic geometric classifier, not the RandLA-Net output. It provides four topic streams that are useful for visualization and experiments, but it should not be described as a deep-learning semantic pipeline.

### Website and live data path

The website consists of a FastAPI backend and a React frontend. At startup, the backend creates ROS 2 subscriptions for the configured terrain point-cloud topics and the configured grid-map topic. It forwards updates to browser clients over a WebSocket at `/ws`. The frontend stores those updates in a Zustand store. Its LiDAR view draws the four configured point-cloud streams in separate 3D panels, and its grid view renders the incoming grid-map layer as a continuous elevation heatmap.

The default website grid topic, `/fastdem/mapping/gridmap`, matches FastDEM's ROS 2 publisher. The configured terrain panel topics match the outputs of the separate RANSAC-based terrain-analysis node when it is running. The backend samples large point clouds down to at most 10,000 points per cloud for browser transfer.

The website currently forwards an elevation layer from the `GridMap`; it does not subscribe to `/point_labels`, `/segmented_points`, `/obstacles`, or `/obstacle_markers`. As a result, the browser does not yet display the RandLA-Net semantic classes or cluster detections overlaid on the FastDEM elevation map. The four terrain panels are also separate topic views, not semantic layers in each grid cell.

The website configuration lists near, middle, and far resolutions, and a mock grid generator can create sample cells at different sizes. The live FastAPI path does not call that generator: it subscribes to the ROS `GridMap` and forwards one map resolution. The website README's variable-resolution description therefore reflects the intended or mock presentation, not the current live map stream.

The dashboard's FPS and people-count values are demo metrics: the backend generates FPS randomly from a configured range and uses a configured constant person count. They are not measurements from the segmentation node or mapping runtime. A separate memory-comparison utility can compare incoming raw-cloud and GridMap message sizes, but this is not a complete process-RAM benchmark and does not establish a fixed percentage saving across runs.

### Existing tests and evidence

FastDEM includes integration tests for map updates, empty clouds, filtering, repeated observations, raycasting, sensor models, estimator options, and local versus global mapping behavior. These tests are useful evidence for the mapping library's core behavior. They do not test a variable-resolution grid, a complete RandLA-Net-to-map path, or the website's end-to-end ROS-to-browser display.

The repository and supplied presentation material mention results such as 73.2% memory reduction, 12.8 FPS, and 95.8% mIoU. Those numbers should be treated as presentation claims until they are reproduced by a documented benchmark using the current code, fixed inputs, known hardware, and clearly defined measurement procedures. In particular, the website's current FPS display is simulated, not a source for validating the slide's FPS figure.

## End-to-end target data flow

The intended runtime can be understood as a set of ROS 2 stages with explicit message contracts:

1. **Acquire:** A simulated or physical LiDAR publishes timestamped `sensor_msgs/msg/PointCloud2` scans, initially using `/velodyne_points`.
2. **Prepare:** Validate the point fields, remove invalid or out-of-range samples, transform points into a consistent map or vehicle frame, and optionally apply a measured voxel or outlier filter. Preserve timestamps and frame IDs through each stage.
3. **Classify:** Run the learned point-cloud model to estimate terrain, static-object, and moving-object classes. Keep class confidence and document the mapping from the checkpoint's labels to the project's class definitions. Use geometric terrain analysis as a baseline or fallback, not as if it were the learned result.
4. **Estimate motion and objects:** Cluster relevant points into object proposals. For moving objects, associate detections across scans and estimate motion; publish detections with timestamps and confidence rather than relying only on a per-point class label.
5. **Project into the foveated map:** Route each valid point to exactly one resolution band, aggregate its elevation and semantic evidence into an aligned cell, and update uncertainty and observation time. Publish the result using a message format that explicitly describes the resolution band and cell geometry.
6. **Consume:** Navigation can use traversability, elevation, and obstacle layers. The website backend subscribes to the map and selected perception topics, then forwards a bounded, versioned payload over WebSocket.
7. **Inspect and measure:** The browser displays elevation and semantic layers with a legend and status derived from real timestamps and node measurements. A separate benchmark records accuracy, latency, throughput, and memory against a consistent baseline.

In the current repository, FastDEM provides much of the mapping foundation, the segmentation and terrain-analysis nodes provide separate perception experiments, and the website already receives ROS 2 data. The classification-to-map path and true multi-resolution representation are the main integration steps still needed.

## Variable-resolution grid design

A conventional `grid_map_msgs/msg/GridMap` describes a grid with one resolution. It cannot faithfully describe neighboring cells with different sizes in one ordinary layer. Sending a foveated map as if it were a single-resolution GridMap would lose the cell geometry or require resampling away the intended benefit.

A practical first implementation is a set of concentric or tiled grid bands, each with its own regular resolution. For example, a fine near-field grid can cover the immediate safety zone, and coarser outer bands can cover farther distances. Each band remains a regular grid internally, which keeps indexing and aggregation straightforward. A custom ROS message can carry the band bounds, resolution, origin, dimensions, layer names, and flattened cell values. Alternatively, publish each band separately with a shared metadata contract.

To avoid gaps, overlap, or drifting alignment:

- Define all band boundaries in one stable map frame and anchor cell origins to a shared world-grid origin.
- Make coarser cell sizes integer multiples of the fine size where possible.
- Assign each position to exactly one band using documented half-open boundaries, for example `$r_i \leq r < r_{i+1}$`.
- Convert world coordinates to indices with one tested quantization rule; do not round independently in each consumer.
- When moving from finer to coarser cells, aggregate elevation and semantic evidence with an explicit policy. Preserve extrema for hazards rather than averaging away a curb or obstacle.
- Keep uncertainty, class confidence, counts, and age available so that sparse distant observations are not mistaken for certainty.
- Define how robot motion, map rolling, and global coordinates affect the band origins.

The website currently expects a single GridMap resolution and a single numeric layer. It will need a corresponding multi-band decoder and a display strategy that draws each band at its real cell size. That makes variable resolution visible instead of silently flattening it into one grid.

## Evaluation plan

The project should show that the foveated representation saves resources without hiding safety-relevant structure. Evaluation should compare methods on the same recorded scans, hardware, map bounds, and processing conditions.

### Accuracy and map quality

- Report per-class intersection-over-union and mean IoU for the actual segmentation checkpoint and evaluation dataset, including results grouped by distance.
- Measure elevation MAE or RMSE against available ground truth, with separate results for flat ground, slopes, steps, potholes, and raised obstacles.
- Evaluate object detection precision and recall, and report motion-classification or tracking performance separately from static object classification.
- Count missed or geometrically distorted hazards at band transitions, especially objects that cross a resolution boundary.

### Runtime and resource use

- Measure end-to-end scan-to-map latency, model inference latency, mapping update rate, and browser refresh rate independently.
- Report median and high-percentile latency (such as P95), sustained throughput, and dropped or delayed scans after warm-up.
- Measure peak process memory and serialized bytes for each representation. Compare against a uniform fine-resolution map over the same covered area and a clearly defined 3D baseline.
- State hardware, software versions, input sequence, point count, resolution schedule, map extent, and whether measurements include the model, middleware, and dashboard.
- Repeat each run and report variation. Treat FPS as a measured output, never as a random display value.

Memory comparisons should be like-for-like. A single GridMap message's shallow Python object size is not the same thing as total process RAM, and a 2.5D map should be compared against a baseline covering the same space and carrying equivalent useful information. The target is a demonstrated reduction at an acceptable accuracy and latency, not a preselected percentage.

## Development stages

1. **Make the baseline reproducible.** Run the current Velodyne simulation, FastDEM mapper, terrain-analysis node, segmentation node, and website as separate components. Record the exact launch commands and verify topic names, frame IDs, timestamps, and QoS. Remove or clearly label synthetic dashboard metrics.
2. **Connect semantic results to mapping.** Define class IDs and confidence semantics once. Add a subscriber or adapter that fuses segmentation output with elevation observations. Include tests for point/label alignment, empty scans, invalid points, and timestamp mismatch.
3. **Build the multi-resolution map engine.** Implement resolution bands with shared coordinates, documented boundaries, hazard-preserving aggregation, and a ROS message contract. Add tests for projection at boundaries, robot motion, and round-trip coordinate/index conversion.
4. **Expose map and object layers to the website.** Extend the ROS subscriber and WebSocket schema to forward band metadata, semantic layers, object detections, and measured performance. Render map bands at true scale and display freshness or connection state.
5. **Benchmark and tune.** Compare uniform and foveated modes using the evaluation plan. Adjust the radius bands, cell sizes, filters, and model settings based on measured safety, latency, and memory results.

## Expected impact

If validated, SteelWings can give an autonomous vehicle a more useful balance between local precision and wider awareness. Fine cells near the vehicle can retain the geometry needed to recognize small hazards, while coarser distant cells can reduce the number of map cells that need to be updated, transmitted, and displayed. Semantic and uncertainty layers can help separate safe terrain from obstacles and make the map more actionable than a height image alone.

The dashboard is an important part of the engineering system, not just a presentation screen. It can help developers see whether scans are arriving, whether map and perception outputs are fresh, and where the system is spending time or memory. Its metrics become meaningful only when they are connected to measured runtime data and presented with enough context to reproduce them.

## Scope and claims

SteelWings is best presented today as a working ROS 2 LiDAR mapping and perception prototype with an operational FastDEM elevation mapper, separate point-cloud segmentation and terrain-analysis components, and a ROS-connected visualization dashboard. Its central research and engineering contribution is the planned integration of those pieces into a genuinely foveated, semantic 2.5D map with measured performance.

The current source does not yet demonstrate distance-adaptive cell sizes in the live FastDEM map, semantic class layers in the map consumed by the website, temporally tracked moving objects, or reproducible support for the headline metrics shown in the presentation. Those are clear next milestones and a strong basis for the project proposal; they should be described as goals until implemented and benchmarked.

## Repository references

- FastDEM ROS 2 node and map publishers: `src/FastDEM/ros2/src/fastdem_ros_node.cpp`
- FastDEM local and global map settings: `src/FastDEM/ros2/config/local_mapping.yaml` and `src/FastDEM/ros2/config/global_mapping.yaml`
- Point-cloud rasterization and elevation statistics: `src/FastDEM/fastdem/src/pcd_convert.cpp` and `src/FastDEM/fastdem/src/elevation_mapping.cpp`
- RandLA-Net inference and label mapping: `src/pc_seg_ros2/pc_seg_ros2/seg_infer_node.py` and `src/pc_seg_ros2/pc_seg_ros2/label_map.py`
- DBSCAN object proposals: `src/pc_seg_ros2/pc_seg_ros2/cluster_bbox_node.py`
- RANSAC terrain topics: `src/pc_seg_ros2/pc_seg_ros2/terrain_analysis.py`
- Website ROS subscriptions and WebSocket payload: `website/backend/perception/ros_subscriber.py` and `website/backend/main.py`
- Website ROS topic configuration: `website/config/ros_topics.yaml`
- Browser data store and map rendering: `website/frontend/src/services/websocket.ts` and `website/frontend/src/pages/GridMapView.tsx`
- Demo metrics and memory comparison: `website/backend/perception/processor.py` and `src/pc_seg_ros2/pc_seg_ros2/memory_usage_comparator.py`