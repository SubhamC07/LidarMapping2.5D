export const CLASS_COLORS = {
  0: '#e4edf6', // Flat Ground - Light Gray
  1: '#a8ff35', // Raised Land - Lime
  2: '#ff9b38', // Pothole - Orange
  3: '#ff5666', // Obstacle - Red
};

export const CLASS_NAMES = {
  0: 'FLAT GROUND',
  1: 'RAISED LAND',
  2: 'POTHOLE',
  3: 'OBSTACLE',
};

export default function Legend() {
  return (
    <div className="relative rounded-md border border-white/15 bg-[#101820]/90 p-3 font-mono text-xs text-gray-100 shadow-sm backdrop-blur pointer-events-none">
      <div className="mb-2 border-b border-white/15 pb-1 font-bold text-white">SEMANTIC CLASSES</div>
      <div className="flex flex-col gap-2">
        {Object.entries(CLASS_NAMES).map(([id, name]) => (
          <div key={id} className="flex items-center gap-2">
            <div 
              className="w-3 h-3 rounded-sm" 
              style={{ backgroundColor: CLASS_COLORS[id as unknown as keyof typeof CLASS_COLORS] }}
            ></div>
            <span className="text-gray-200">{name}</span>
          </div>
        ))}
      </div>
    </div>
  );
}
