import { useWebSocket } from '../services/websocket';
import { Activity, AlertTriangle } from 'lucide-react';

export default function StatusBar() {
  const metrics = useWebSocket((state) => state.metrics);

  return (
    <div className="relative z-10 grid shrink-0 grid-cols-2 gap-2 border-t border-gray-300 bg-white px-2 py-2 font-mono shadow-[0_-2px_10px_rgba(0,0,0,0.05)] sm:flex sm:h-12 sm:items-center sm:justify-between sm:px-6 sm:text-sm">
      <div className="flex min-w-0 items-center justify-center gap-2 rounded-md border border-red-200 bg-red-50 px-2 py-1.5 text-red-900 sm:justify-start sm:gap-3 sm:px-4">
        <AlertTriangle size={16} className="shrink-0 animate-pulse text-red-600 sm:h-[18px] sm:w-[18px]" />
        <span className="text-xs font-bold sm:text-sm">PEOPLE</span>
        <span className="text-base font-black sm:text-lg">{metrics.obstacles.toString().padStart(2, '0')}</span>
        
        {metrics.obstacles > 0 && (
          <span className="ml-2 hidden border-l border-red-200 pl-3 text-xs text-red-700 sm:inline">
            {Object.entries(metrics.obstacle_types).map(([type, count]) => (
              `${type}: ${count.toString().padStart(2, '0')}`
            )).join(' | ')}
          </span>
        )}
      </div>

      <div className="flex min-w-0 items-center justify-center gap-2 rounded-md border border-blue-200 bg-blue-50 px-2 py-1.5 text-blue-900 sm:justify-start sm:gap-3 sm:px-4">
        <Activity size={16} className="shrink-0 text-blue-600 sm:h-[18px] sm:w-[18px]" />
        <span className="text-xs font-bold sm:text-sm">FPS</span>
        <span className="w-10 text-right text-base font-black sm:w-12 sm:text-lg">{metrics.fps.toFixed(1)}</span>
      </div>
    </div>
  );
}
