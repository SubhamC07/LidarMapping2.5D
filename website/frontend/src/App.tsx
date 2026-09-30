import { useState, useEffect } from 'react'
import Header from './components/Header'
import StatusBar from './components/StatusBar'
import LidarView from './pages/LidarView'
import GridMapView from './pages/GridMapView'
import { useWebSocket } from './services/websocket'

function App() {
  const [activeTab, setActiveTab] = useState<'lidar' | 'grid'>('lidar')
  const connect = useWebSocket((state) => state.connect)

  useEffect(() => {
    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:'
    connect(`${protocol}//${window.location.hostname}:8000/ws`)
  }, [connect])

  return (
    <div className="flex h-[100dvh] flex-col bg-drdo-gray">
      <Header activeTab={activeTab} onTabChange={setActiveTab} />
      
      <main className="relative min-h-0 flex-1 overflow-y-auto md:overflow-hidden">
        {activeTab === 'lidar' ? <LidarView /> : <GridMapView />}
      </main>

      <StatusBar />
    </div>
  )
}

export default App
