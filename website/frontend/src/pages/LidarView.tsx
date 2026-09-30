import { Component, ReactNode, useEffect, useRef, useMemo } from 'react';
import { Canvas } from '@react-three/fiber';
import { OrbitControls, Grid } from '@react-three/drei';
import * as THREE from 'three';
import { useWebSocket } from '../services/websocket';
import Legend, { CLASS_COLORS } from '../components/Legend';

type CloudTopic = { name: string; topic: string };

const defaultCloudTopics: CloudTopic[] = [
  { name: 'FLAT_GROUND', topic: 'Configuration pending' },
  { name: 'RAISED_LAND', topic: 'Configuration pending' },
  { name: 'POTHOLE', topic: 'Configuration pending' },
  { name: 'OBSTACLE', topic: 'Configuration pending' },
];

// Convert hex colors to THREE.Color for fast lookup
const colors = {
  0: new THREE.Color(CLASS_COLORS[0]),
  1: new THREE.Color(CLASS_COLORS[1]),
  2: new THREE.Color(CLASS_COLORS[2]),
  3: new THREE.Color(CLASS_COLORS[3]),
};

function PointCloudFallback({ pointsData, cloudIndex }: { pointsData: number[]; cloudIndex: number }) {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;

    const draw = () => {
      const bounds = canvas.getBoundingClientRect();
      const ratio = window.devicePixelRatio || 1;
      canvas.width = Math.max(1, Math.round(bounds.width * ratio));
      canvas.height = Math.max(1, Math.round(bounds.height * ratio));
      const context = canvas.getContext('2d');
      if (!context) return;

      context.fillStyle = '#030609';
      context.fillRect(0, 0, canvas.width, canvas.height);
      let minX = Infinity;
      let maxX = -Infinity;
      let minY = Infinity;
      let maxY = -Infinity;

      for (let index = 0; index < pointsData.length; index += 4) {
        const x = pointsData[index];
        const y = pointsData[index + 1];
        if (!Number.isFinite(x) || !Number.isFinite(y)) continue;
        minX = Math.min(minX, x);
        maxX = Math.max(maxX, x);
        minY = Math.min(minY, y);
        maxY = Math.max(maxY, y);
      }
      if (!Number.isFinite(minX)) return;

      const padding = 18 * ratio;
      const spanX = maxX - minX || 1;
      const spanY = maxY - minY || 1;
      const scale = Math.min(
        (canvas.width - padding * 2) / spanX,
        (canvas.height - padding * 2) / spanY,
      );
      const drawWidth = spanX * scale;
      const drawHeight = spanY * scale;
      const offsetX = (canvas.width - drawWidth) / 2;
      const offsetY = (canvas.height - drawHeight) / 2;

      context.fillStyle = CLASS_COLORS[cloudIndex as keyof typeof CLASS_COLORS];
      for (let index = 0; index < pointsData.length; index += 4) {
        const x = pointsData[index];
        const y = pointsData[index + 1];
        if (!Number.isFinite(x) || !Number.isFinite(y)) continue;
        const pixelX = offsetX + (x - minX) * scale;
        const pixelY = canvas.height - offsetY - (y - minY) * scale;
        context.fillRect(pixelX, pixelY, 3 * ratio, 3 * ratio);
      }
    };

    const observer = new ResizeObserver(draw);
    observer.observe(canvas);
    draw();
    return () => observer.disconnect();
  }, [pointsData, cloudIndex]);

  return <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" aria-label="2D point cloud fallback" />;
}

class WebGLBoundary extends Component<{ children: ReactNode; fallback: ReactNode }, { failed: boolean }> {
  state = { failed: false };

  static getDerivedStateFromError() {
    return { failed: true };
  }

  render() {
    if (this.state.failed) {
      return this.props.fallback;
    }

    return this.props.children;
  }
}

function PointCloud({ pointsData }: { pointsData: number[] }) {
  const geometryRef = useRef<THREE.BufferGeometry>(null);
  
  // Pre-allocate buffer arrays to avoid recreating them every frame
  const maxPoints = 10000;
  const positions = useMemo(() => new Float32Array(maxPoints * 3), []);
  const colorArray = useMemo(() => new Float32Array(maxPoints * 3), []);

  useEffect(() => {
    if (!geometryRef.current || !pointsData.length) return;

    let numPoints = Math.min(pointsData.length / 4, maxPoints);

    for (let i = 0; i < numPoints; i++) {
      const idx = i * 4;
      const x = pointsData[idx];
      const y = pointsData[idx + 1];
      const z = pointsData[idx + 2];
      const c = pointsData[idx + 3] as keyof typeof colors;

      // Swap Y and Z for ThreeJS coordinate system (Z is up in ROS usually)
      positions[i * 3] = x;
      positions[i * 3 + 1] = z;
      positions[i * 3 + 2] = -y;

      const color = colors[c] || colors[0];
      colorArray[i * 3] = color.r;
      colorArray[i * 3 + 1] = color.g;
      colorArray[i * 3 + 2] = color.b;
    }

    geometryRef.current.setAttribute('position', new THREE.BufferAttribute(positions.subarray(0, numPoints * 3), 3));
    geometryRef.current.setAttribute('color', new THREE.BufferAttribute(colorArray.subarray(0, numPoints * 3), 3));
    
    // Set draw range so we only render the points we have
    geometryRef.current.setDrawRange(0, numPoints);
    
    geometryRef.current.attributes.position.needsUpdate = true;
    geometryRef.current.attributes.color.needsUpdate = true;
  }, [pointsData, positions, colorArray]);

  return (
    <points>
      <bufferGeometry ref={geometryRef} />
      <pointsMaterial 
        size={3} 
        vertexColors 
        sizeAttenuation={false}
      />
    </points>
  );
}

export default function LidarView() {
  const pointClouds = useWebSocket((state) => state.pointClouds);
  const cloudTopics = useWebSocket((state): CloudTopic[] =>
    state.config?.ros?.lidar?.pointcloud_topics ?? defaultCloudTopics,
  );

  return (
    <div className="relative w-full bg-[#030609] md:h-full">
      <div className="grid auto-rows-[minmax(14rem,42dvh)] grid-cols-1 gap-2 p-2 md:h-full md:auto-rows-auto md:grid-cols-2 md:grid-rows-2 md:gap-px md:bg-[#26323a] md:p-0">
        {cloudTopics.map((cloud, index) => (
          <section key={cloud.name} className="relative min-h-0 min-w-0 overflow-hidden rounded-sm border border-white/10 bg-[#030609] md:rounded-none">
            <div className="absolute left-2 top-2 z-10 border-l-2 bg-[#101820]/90 px-2 py-1 font-mono text-[10px] text-gray-100 shadow-sm sm:left-3 sm:top-3" style={{ borderColor: CLASS_COLORS[index as keyof typeof CLASS_COLORS] }}>
              <div>CLOUD 0{index + 1} · {cloud.name}</div>
              <div className="text-[9px] text-gray-300">{cloud.topic}</div>
            </div>
            <WebGLBoundary fallback={<PointCloudFallback pointsData={pointClouds[index] ?? []} cloudIndex={index} />}>
              <Canvas camera={{ position: [-15, 15, 20], fov: 50 }}>
                <color attach="background" args={['#030609']} />
                <Grid
                  infiniteGrid
                  fadeDistance={50}
                  sectionColor="#28343d"
                  cellColor="#101820"
                  position={[0, -0.01, 0]}
                />
                <axesHelper args={[5]} />
                <PointCloud pointsData={pointClouds[index] ?? []} />
                <OrbitControls makeDefault />
              </Canvas>
            </WebGLBoundary>
          </section>
        ))}
      </div>
      <div className="absolute bottom-3 right-3 z-10 hidden md:block">
        <Legend />
      </div>
    </div>
  );
}
