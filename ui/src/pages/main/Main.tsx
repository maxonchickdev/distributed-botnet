import { Button, Input } from 'antd'
import { useState } from 'react'
import { MainLayout } from '../../Layouts/MainLayout'
import { Services } from '../../services/Services'
import styles from './Main.module.css'

const { TextArea } = Input

export const Main = () => {
  const [url, setUrl] = useState<string>('')
  const [botsState, setBotsState] = useState<string>('false')

  const pushUrl = async () => {
    const responseUrl = await Services.pushUrl(url)
    setUrl('')
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
    <MainLayout>
      <div className={styles.flex_wrapper}>
        <TextArea
          value={url}
          onChange={e => setUrl(e.target.value)}
          placeholder='Controlled autosize'
          // autoSize={{ minRows: 3, maxRows: 5 }}
        />
        <Button type='primary' onClick={pushUrl} className={styles.button}>
          Push URL
        </Button>
      </div>
      <div className={styles.buttons_wrapper}>
        <Button
          type='dashed'
          onClick={handleStartClick}
          className={styles.control_button}
        >
          Run bots
        </Button>
        <Button
          type='dashed'
          onClick={handleStopClick}
          className={styles.control_button}
        >
          Stop bots
        </Button>
      </div>
      {/* <Plot /> */}
    </MainLayout>
  )
}
