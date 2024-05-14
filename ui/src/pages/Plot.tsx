import { Chart } from 'react-google-charts'

const Plot = ({ statusCodes }) => {
  const data = [['Status Code', 'Times'], ...statusCodes]
  return (
    <Chart
      chartType='PieChart'
      height='450px'
      data={data}
      options={{
        legend: 'none', // Hide the legend
        chartArea: { left: 50, top: 50, width: '80%', height: '80%' }, // Adjust chart area
      }}
      chartPackages={['corechart', 'controls']}
    />
  )
}

export default Plot
