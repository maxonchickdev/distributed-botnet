// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <mutex>
#include <string>
#include <cpr/cpr.h>

void task_for_thread(std::mutex &m, int &success_responces, int upper_bound_response, std::string URL)
{
	int counter = 0;
	for (int i = 0; i < upper_bound_response; ++i)
	{
		cpr::Response inner_request = cpr::Get(cpr::Url{URL});
		if (inner_request.status_code == 200)
		{
			std::cout << inner_request.status_code << std::endl;
			++counter;
		}
	}

	m.lock();
	success_responces += counter;
	m.unlock();
}