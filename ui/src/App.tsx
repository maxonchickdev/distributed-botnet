import { useState } from 'react'
import { Services } from './services/Services'

export const App = () => {
  const [url, setUrl] = useState<string>('')
  const [botsState, setBotsState] = useState<string>('false')

  const pushUrl = async () => {
    const responseUrl = await Services.pushUrl(url)
    return responseUrl
  }

  const botsActivate = async (ready: string) => {
    const requestStart = await Services.pushStart(ready)
    return requestStart
  }

  console.log(botsState)

  const handleStartClick = async () => {
    setBotsState('true')
    await botsActivate('true')
  }

  const handleStopClick = async () => {
    setBotsState('false')
    await botsActivate('false')
  }

  return (
    <div>
      <input type='text' onChange={e => setUrl(e.target.value)} />
      <button onClick={pushUrl}>Submit URL</button>
      <button onClick={handleStartClick}>Start</button>
      <button onClick={handleStopClick}>Stop</button>
      {/* <Plot /> */}
    </div>
  )
}
