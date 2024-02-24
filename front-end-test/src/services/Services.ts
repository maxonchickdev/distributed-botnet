import axios from 'axios'

export const Services = {
	async getData() {
		const response = await axios.get('http://0.0.0.0:8080/')
		return response.data
	},
}
