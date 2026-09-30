import { useEffect, useRef } from 'react';
import { useWebSocket } from '../services/websocket';

export default function GridMapView() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const gridMap = useWebSocket((state) => state.gridMap);
  const topic = useWebSocket((state) => state.config?.ros?.map?.grid_topic ?? '');

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;

    const draw = () => {
      const bounds = canvas.getBoundingClientRect();
      const pixelRatio = window.devicePixelRatio || 1;
      canvas.width = Math.max(1, Math.round(bounds.width * pixelRatio));
      canvas.height = Math.max(1, Math.round(bounds.height * pixelRatio));
      const context = canvas.getContext('2d');
      if (!context) return;

      context.fillStyle = '#020508';
      context.fillRect(0, 0, canvas.width, canvas.height);
      if (!gridMap || !gridMap.width || !gridMap.height) return;

      const image = document.createElement('canvas');
      image.width = gridMap.width;
      image.height = gridMap.height;
      const imageContext = image.getContext('2d');
      if (!imageContext) return;

      const sortedValues = gridMap.values
        .filter((value): value is number => value !== null && Number.isFinite(value))
        .sort((first, second) => first - second);
      if (!sortedValues.length) return;

      const lower = sortedValues[Math.floor((sortedValues.length - 1) * 0.05)];
      const upper = sortedValues[Math.floor((sortedValues.length - 1) * 0.95)];
      const span = upper - lower || 1;
      const pixels = imageContext.createImageData(gridMap.width, gridMap.height);

      gridMap.values.forEach((value, index) => {
        const pixel = index * 4;
        if (value === null || !Number.isFinite(value)) {
          pixels.data[pixel + 3] = 0;
          return;
        }

        const amount = Math.max(0, Math.min(1, (value - lower) / span));
        const stops = [
          [54, 189, 230],
          [108, 230, 173],
          [255, 228, 92],
        ];
        const segment = amount <= 0.5 ? 0 : 1;
        const segmentAmount = amount <= 0.5 ? amount * 2 : (amount - 0.5) * 2;
        const start = stops[segment];
        const end = stops[segment + 1];
        pixels.data[pixel] = Math.round(start[0] + (end[0] - start[0]) * segmentAmount);
        pixels.data[pixel + 1] = Math.round(start[1] + (end[1] - start[1]) * segmentAmount);
        pixels.data[pixel + 2] = Math.round(start[2] + (end[2] - start[2]) * segmentAmount);
        pixels.data[pixel + 3] = 255;
      });
      imageContext.putImageData(pixels, 0, 0);

      const mapWidth = gridMap.length_x || gridMap.width * gridMap.resolution;
      const mapHeight = gridMap.length_y || gridMap.height * gridMap.resolution;
      const scale = Math.min(canvas.width / mapWidth, canvas.height / mapHeight);
      const drawWidth = mapWidth * scale;
      const drawHeight = mapHeight * scale;
      context.imageSmoothingEnabled = false;
      context.drawImage(
        image,
        (canvas.width - drawWidth) / 2,
        (canvas.height - drawHeight) / 2,
        drawWidth,
        drawHeight,
      );
    };

    const observer = new ResizeObserver(draw);
    observer.observe(canvas);
    draw();
    return () => observer.disconnect();
  }, [gridMap]);

  return (
    <div className="relative h-full w-full overflow-hidden bg-[#020508]">
      <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" aria-label="ROS 2 grid map" />
      <div className="absolute left-3 top-3 z-10 max-w-[calc(100%-1.5rem)] border-l-2 border-cyan-400 bg-[#101820]/90 px-3 py-2 font-mono text-[10px] text-gray-100 shadow-sm sm:left-4 sm:top-4">
        <div className="font-bold text-white">GRID MAP</div>
        <div className="break-all text-gray-300">{topic}</div>
        <div className="text-gray-200">
          {gridMap
            ? `${gridMap.width} × ${gridMap.height} · ${gridMap.resolution} m · ${gridMap.values.filter((value) => value !== null && Number.isFinite(value)).length} valid cells`
            : 'Waiting for grid map message'}
        </div>
      </div>
    </div>
  );
}
