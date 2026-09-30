import { useWebSocket } from '../services/websocket';
import { ShieldCheck } from 'lucide-react';

interface HeaderProps {
  activeTab: 'lidar' | 'grid';
  onTabChange: (tab: 'lidar' | 'grid') => void;
}

export default function Header({ activeTab, onTabChange }: HeaderProps) {
  const connected = useWebSocket((state) => state.connected);

  return (
    <header className="relative z-10 grid shrink-0 gap-2 border-b border-gray-200 bg-white px-3 py-2 shadow-sm sm:flex sm:items-center sm:justify-between sm:px-6 sm:py-3">
      <div className="min-w-0">
        <h1 className="flex items-center gap-2 text-base font-bold text-drdo-blue sm:text-xl">
          <ShieldCheck size={20} className="shrink-0 text-blue-700 sm:h-6 sm:w-6" />
          <span className="truncate">DEFENCE PERCEPTION SYSTEM</span>
        </h1>
        <div className="mt-1 hidden font-mono text-xs text-gray-500 sm:block">
          Adaptive 2.5D LiDAR Mapping | SIH26053 | Real-Time Dynamic Environment Perception
        </div>
      </div>
      
      <div className="grid min-w-0 grid-cols-[minmax(0,1fr)_auto] items-center gap-2 sm:flex sm:gap-6">
        <div className="flex min-w-0 rounded-md border border-gray-200 bg-gray-100 p-1">
          <button
            onClick={() => onTabChange('lidar')}
            className={`min-w-0 flex-1 rounded px-2 py-2 text-[11px] font-semibold leading-tight sm:flex-none sm:px-4 sm:py-1.5 sm:text-sm ${activeTab === 'lidar' ? 'bg-white text-drdo-blue shadow-sm' : 'text-gray-500 hover:text-gray-700'}`}
          >
            <span className="sm:hidden">CLOUDS · 4</span>
            <span className="hidden sm:inline">3D POINT CLOUDS · 4</span>
          </button>
          <button
            onClick={() => onTabChange('grid')}
            className={`min-w-0 flex-1 rounded px-2 py-2 text-[11px] font-semibold leading-tight sm:flex-none sm:px-4 sm:py-1.5 sm:text-sm ${activeTab === 'grid' ? 'bg-white text-drdo-blue shadow-sm' : 'text-gray-500 hover:text-gray-700'}`}
          >
            <span className="sm:hidden">GRID MAP</span>
            <span className="hidden sm:inline">2.5D GRID MAP</span>
          </button>
        </div>

        <div className="grid grid-cols-3 gap-1 font-mono text-[8px] sm:flex sm:flex-col sm:gap-1 sm:text-[10px]">
          <div className="flex items-center gap-2">
            <span className={`h-1.5 w-1.5 shrink-0 rounded-full sm:h-2 sm:w-2 ${connected ? 'bg-green-500' : 'bg-red-500'}`}></span>
            <span className="hidden w-24 text-gray-600 sm:inline">STREAM</span>
            <span className="font-bold text-gray-800">{connected ? 'CONNECTED' : 'OFFLINE'}</span>
          </div>
          <div className="flex items-center gap-2">
            <span className={`h-1.5 w-1.5 shrink-0 rounded-full sm:h-2 sm:w-2 ${connected ? 'bg-green-500' : 'bg-gray-400'}`}></span>
            <span className="hidden w-24 text-gray-600 sm:inline">CLOUDS</span>
            <span className="font-bold text-gray-800">{connected ? 'ACTIVE' : 'WAITING'}</span>
          </div>
          <div className="flex items-center gap-2">
            <span className="h-1.5 w-1.5 shrink-0 rounded-full bg-blue-500 sm:h-2 sm:w-2"></span>
            <span className="hidden w-24 text-gray-600 sm:inline">SYSTEM</span>
            <span className="font-bold text-gray-800">READY</span>
          </div>
        </div>
      </div>
    </header>
  );
}
