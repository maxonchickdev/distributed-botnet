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
  return (
    <div>
      <input type='text' onChange={e => setUrl(e.target.value)} />
      <button onClick={pushUrl}>Submit URL</button>
      <button
        onClick={() => {
          setBotsState('true')
          botsActivate(botsState)
        }}
      >
        Start
      </button>
      <button
        onClick={() => {
          setBotsState('false')
          botsActivate(botsState)
        }}
      >
        Stop
      </button>
      {/* <Plot /> */}
    </div>
  )
}
