import { Button, Input } from 'antd'
import { useEffect, useState } from 'react'
import { MainLayout } from '../../Layouts/MainLayout'
import { Services } from '../../services/Services'

const { TextArea } = Input

export const Main = () => {
  const [url, setUrl] = useState<string>('')
  const [botsState, setBotsState] = useState<string>('false')
  const [statusCodes, setStatusCodes] = useState<string>('')

  const urlToMaster = async () => {
    const responseUrl = await Services.pushUrl(url)
    setUrl('')
    return responseUrl
  }

  const botsActivate = async (ready: string) => {
    const requestStart = await Services.pushStart(ready)
    return requestStart
  }

  const handleStartClick = async () => {
    setBotsState('true')
    await botsActivate('true')
  }

  const handleStopClick = async () => {
    setBotsState('false')
    await botsActivate('false')
  }

  useEffect(() => {
    const handleStatusCodes = async () => {
      const responseCodes = await Services.reciveStatusCodes()
      setStatusCodes(responseCodes)
    }
    handleStatusCodes()
  }, [botsState])

  console.log(statusCodes)

  return (
    <MainLayout>
      <div className='absolute top-1/2 left-1/2 translate-x-[-50%] translate-y-[-50%] max-w-[400px] w-[100%]'>
        <TextArea
          value={url}
          onChange={e => setUrl(e.target.value)}
          placeholder='Enter target URL'
          className='mb-3'
          // autoSize={{ minRows: 3, maxRows: 5 }}
        />
        <Button type='primary' block className='mb-3' onClick={urlToMaster}>
          Push
        </Button>

        <div className='flex justify-between'>
          <Button value={botsState} onClick={handleStartClick}>
            Run bots
          </Button>
          <Button value={botsState} onClick={handleStopClick}>
            Stop bots
          </Button>
        </div>
      </div>
      {/* <Plot /> */}
    </MainLayout>
  )
}
