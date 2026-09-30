import { create } from 'zustand'

interface SystemMetrics {
  fps: number;
  obstacles: number;
  obstacle_types: Record<string, number>;
}

interface GridMapData {
  width: number;
  height: number;
  resolution: number;
  length_x: number;
  length_y: number;
  layer: string;
  values: Array<number | null>;
}

interface AppState {
  connected: boolean;
  pointClouds: number[][];
  gridMap: GridMapData | null;
  metrics: SystemMetrics;
  config: any;
  connect: (url: string) => void;
  disconnect: () => void;
}

export const useWebSocket = create<AppState>((set, get) => {
  let ws: WebSocket | null = null;

  return {
    connected: false,
    pointClouds: [],
    gridMap: null,
    metrics: { fps: 0, obstacles: 0, obstacle_types: {} },
    config: null,

    connect: (url: string) => {
      if (ws) return;
      
      ws = new WebSocket(url);

      ws.onopen = () => {
        set({ connected: true });
      };

      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'CONFIG') {
            set({ config: data.config });
          } else if (data.type === 'PERCEPTION_UPDATE') {
            set({
              pointClouds: data.point_clouds,
              gridMap: data.grid_map,
              metrics: data.metrics
            });
          }
        } catch (e) {
          console.error("Error parsing websocket message", e);
        }
      };

      ws.onclose = () => {
        set({ connected: false });
        ws = null;
        // Reconnect logic could be here, respecting config.reconnect_interval
        setTimeout(() => get().connect(url), 2000);
      };

      ws.onerror = (error) => {
        console.error("WebSocket error:", error);
      };
    },

    disconnect: () => {
      if (ws) {
        ws.close();
        ws = null;
      }
    }
  };
});
