import { useState } from 'react'
import { Services } from './services/Services'

export const App = () => {
  const [url, setUrl] = useState<string>('')
  const pushUrl = async () => {
    const responseUrl = await Services.pushUrl(url);
    return responseUrl;
  }
  return (
    <div>
      <input type='text' onChange={e => setUrl(e.target.value)} />
      <button onClick={pushUrl}>Submit</button>
    </div>
  )
}
