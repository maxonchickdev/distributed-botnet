import axios from 'axios'

export const Services = {
  async pushUrl(url: string) {
    const response = await axios.post<string>(
      'http://localhost:8080/get-url/',
      url
    )
    return response.data
  },
  async pushStart(state: string) {
    const response = await axios.post<string>(
      'http://localhost:8080/recive-bots-state/',
      state
    )
    return response.data
  },
}
