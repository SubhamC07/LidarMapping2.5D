# Adaptive 2.5D LiDAR Mapping (SIH26053)

A Linux dashboard for viewing four ROS 2 point-cloud topics and a variable-resolution 2.5D grid map. The browser receives updates from a FastAPI WebSocket service.

## What You See

- The first tab shows the `FLAT_GROUND`, `RAISED_LAND`, `POTHOLE`, and `OBSTACLE` point clouds in a 2×2 layout. Each panel subscribes to its configured ROS 2 `PointCloud2` topic.
- The second tab subscribes to the configured ROS 2 grid-map topic and displays its numeric layer as a continuous grayscale map without semantic classification.
- FPS is generated independently for each update and fluctuates between 10 and 15.
- The displayed person count is held at one.
- Point clouds and the grid map are received from ROS 2. FPS and person count are generated demo metrics, not sensor or model readings.

## Requirements

- Linux
- ROS 2 Humble, with `rclpy`, `sensor_msgs`, `sensor_msgs_py`, and `grid_map_msgs`
- Python 3.9 or newer, with `venv` support
- Node.js 18 or newer and npm

On Ubuntu/Debian, install Python tooling with:

```bash
sudo apt update
sudo apt install python3 python3-venv python3-pip
```

Install Node.js 18 or newer using a trusted Linux package source, then verify versions:

```bash
python3 --version
node --version
npm --version
```

## Run the Application

Open two terminals from the project root.

### Terminal 1: Backend

```bash
source /opt/ros/humble/setup.bash
export ROS_DOMAIN_ID=0
cd backend
python3 -m venv --system-site-packages .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
uvicorn main:app --reload --host 0.0.0.0 --port 8000
```

The backend serves the WebSocket on port `8000`. The frontend connects to the same host that served the page.

### Terminal 2: Frontend

```bash
cd frontend
npm install
npm run dev -- --host 0.0.0.0 --port 5173
```

Open the local URL printed by Vite, normally `http://localhost:5173`.

### Open on a Phone

1. Connect the phone and computer to the same trusted Wi-Fi network.
2. Keep both servers running. Start the backend with the ROS setup and `ROS_DOMAIN_ID=0` shown above.
3. Find the computer's Wi-Fi IPv4 address with `hostname -I`.
4. On the phone, open `http://<computer-ip>:5173` (for example, `http://192.168.1.25:5173`).
5. If the page loads but shows `DISCONNECTED`, allow inbound TCP ports `5173` and `8000` through the computer's firewall on the trusted network.

The browser connects to the backend WebSocket at `ws://<computer-ip>:8000/ws`. Do not use `localhost` on the phone; that points to the phone itself.

## Configuration

Edit `config/system.yaml` for generated metric settings:

- `simulation.enabled` enables generated FPS and person-count metrics.
- `simulation.update_rate_hz` sets the stream update rate.
- `simulation.fps_min` and `simulation.fps_max` set the generated FPS range.
- `simulation.people_detected` sets the constant displayed person count.

Edit `config/ros_topics.yaml` to configure the ROS inputs:

- `ros.lidar.pointcloud_topics` contains four ordered `sensor_msgs/msg/PointCloud2` topics for the `FLAT_GROUND`, `RAISED_LAND`, `POTHOLE`, and `OBSTACLE` panels.
- `ros.map.grid_topic` is the single `grid_map_msgs/msg/GridMap` topic displayed in the second tab. The backend forwards its `elevation` layer when present, otherwise the first non-classification numeric layer; no classified cells are rendered.

Confirm configured topics with `ROS_DOMAIN_ID=0 ros2 topic list -t`. A panel remains empty until its topic has a publisher. FPS and person count are generated demo metrics and must not be interpreted as sensor or model readings.

## Production Build

From `frontend/`, run:

```bash
npm run build
```
