import { useEffect, useState } from 'react'
import { Services } from './services/Services'

export const App = () => {
	const [data, setData] = useState<string>('')
	useEffect(() => {
		const getHello = async () => {
			const responseData = await Services.getData()
			setData(responseData)
			return responseData
		}
		getHello()
	}, [])
	console.log(data)

	return <>Hello</>
}
