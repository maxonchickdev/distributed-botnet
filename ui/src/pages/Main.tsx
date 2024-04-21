import { Button, Input } from 'antd'
import { useEffect, useState } from 'react'
import { MainLayout } from '../Layouts/MainLayout'
import { Services } from '../services/Services'

const { TextArea } = Input

export const Main = () => {
  const [url, setUrl] = useState<string>('')
  const [botsState, setBotsState] = useState<string>('false')
  const [statusCodes, setStatusCodes] = useState<string>('')
  const [botsStart, setBotsStart] = useState<boolean>(false)
  const [botsStop, setBotsStop] = useState<boolean>(true)
  const [area, setArea] = useState<boolean>(false)
  const [push, setPush] = useState<boolean>(false)
  const [pool, setPool] = useState<boolean>(false)

  const pushUrl = async () => {
    const responseUrl = await Services.pushUrl(url)
    setArea(true)
    setPush(true)
    setBotsStart(true)
    return responseUrl
  }

  const botsActivation = async (ready: string) => {
    const requestStart = await Services.pushStart(ready)
    return requestStart
  }

  const handleClick = async (state: string) => {
    setBotsState(state)
    await botsActivation(state)
    if (state === 'true') {
      setBotsStart(false)
      setBotsStop(false)
      setPool(true)
    } else if (state === 'false') {
      setBotsStart(true)
      setBotsStop(true)
      setArea(false)
      setPush(false)
      setPool(false)
      setStatusCodes('')
    }
  }

  useEffect(() => {
    console.log('pool', botsStart)
    if (botsStart === false && pool === true) {
      const interval = setInterval(async () => {
        const response = await Services.getData()
        setStatusCodes(response)
        console.log(botsState)
      }, 1000)

      return () => {
        clearInterval(interval)
      }
    }
  }, [botsStart])

  return (
    <MainLayout>
      <div className='absolute top-1/2 left-1/2 translate-x-[-50%] translate-y-[-50%] max-w-[400px] w-[100%]'>
        <TextArea
          value={url}
          onChange={e => setUrl(e.target.value)}
          placeholder='Enter target URL'
          className='mb-3'
          disabled={area}
        />
        <Button
          type='primary'
          block
          className='mb-3'
          onClick={pushUrl}
          disabled={push}
        >
          Push
        </Button>
        <div className='flex justify-between'>
          <Button onClick={() => handleClick('true')} disabled={!botsStart}>
            Run bots
          </Button>
          <Button onClick={() => handleClick('false')} disabled={botsStop}>
            Stop bots
          </Button>
        </div>
      </div>
      {statusCodes}
      {/* <Plot /> */}
    </MainLayout>
  )
}
