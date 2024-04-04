import React from 'react'

export const MainLayout = ({ children }: { children: React.ReactNode }) => {
  return (
    <div className='max-w-[1220px] px-[10px] mx-auto my-0 w-[100%] h-full'>
      {children}
    </div>
  )
}
