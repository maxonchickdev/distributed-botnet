import { Button, Input } from 'antd'
import { useEffect, useState } from 'react'
import { MainLayout } from '../Layouts/MainLayout'
import { Services } from '../services/Services'

const { TextArea } = Input

export const Main = () => {
  const [url, setUrl] = useState<string>('')
  const [botsState, setBotsState] = useState<string>('false')
  const [statusCodes, setStatusCodes] = useState<string>('')
  const [pool, setPool] = useState<boolean>(false)
  const [testState, setTestState] = useState<boolean>(false)

  const pushUrl = async () => {
    const responseUrl = await Services.pushUrl(url)
    setTestState(true)
    return responseUrl
  }

  const botsActivate = async (ready: string) => {
    const requestStart = await Services.pushStart(ready)
    return requestStart
  }

  const handleClick = async (state: string) => {
    setBotsState(state)
    await botsActivate(state)
    if (state === 'true') {
      setPool(true)
    } else {
      setPool(false)
    }
  }

  useEffect(() => {
    console.log('pool', pool)
    if (pool) {
      const interval = setInterval(async () => {
        const response = await Services.getData()
        setStatusCodes(response)
        console.log(botsState)
      }, 1000)

      return () => {
        clearInterval(interval)
      }
    }
  }, [pool])

  return (
    <MainLayout>
      <div className='absolute top-1/2 left-1/2 translate-x-[-50%] translate-y-[-50%] max-w-[400px] w-[100%]'>
        <TextArea
          value={url}
          onChange={e => setUrl(e.target.value)}
          placeholder='Enter target URL'
          className='mb-3'
          disabled={testState}
        />
        <Button type='primary' block className='mb-3' onClick={pushUrl}>
          Push
        </Button>
        <div className='flex justify-between'>
          <Button onClick={() => handleClick('true')} disabled={pool}>
            Run bots
          </Button>
          <Button onClick={() => handleClick('false')} disabled={!pool}>
            Stop bots
          </Button>
        </div>
      </div>
      {statusCodes}
      {/* <Plot /> */}
    </MainLayout>
  )
}
