import asyncio
import json
from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from fastapi.middleware.cors import CORSMiddleware
from websocket.manager import manager
from config_loader import CONFIG
from perception.processor import PerceptionProcessor
from perception.ros_subscriber import RosSubscriber

app = FastAPI(title="DRDO Perception System API")

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

processor = PerceptionProcessor()
ros_subscriber = RosSubscriber(
    CONFIG['ros']['lidar']['pointcloud_topics'],
    CONFIG['ros']['map']['grid_topic'],
    CONFIG['ros']['domain_id'],
)

@app.on_event("startup")
async def startup_event():
    ros_subscriber.start()
    asyncio.create_task(broadcast_perception_data())

@app.on_event("shutdown")
async def shutdown_event():
    ros_subscriber.stop()

async def broadcast_perception_data():
    update_rate = CONFIG['simulation']['update_rate_hz']
    interval = 1.0 / update_rate
    
    while True:
        if not manager.active_connections:
            await asyncio.sleep(1)
            continue
            
        try:
            point_clouds = ros_subscriber.get_point_clouds()
            grid_map = ros_subscriber.get_grid_map()
            if CONFIG['simulation']['enabled']:
                metrics = processor.generate_metrics()
            else:
                metrics = {"fps": 0, "obstacles": 0, "obstacle_types": {}}

            payload = {
                "type": "PERCEPTION_UPDATE",
                "timestamp": asyncio.get_event_loop().time(),
                "point_clouds": point_clouds,
                "grid_map": grid_map,
                "metrics": metrics
            }

            await manager.broadcast(json.dumps(payload))
                
        except Exception as e:
            print(f"Error generating data: {e}")
            
        await asyncio.sleep(interval)

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await manager.connect(websocket)
    try:
        # Send initial config to frontend
        await manager.send_personal_message(json.dumps({
            "type": "CONFIG",
            "config": CONFIG
        }), websocket)
        
        while True:
            data = await websocket.receive_text()
            # Handle incoming messages from frontend if needed
    except WebSocketDisconnect:
        manager.disconnect(websocket)
