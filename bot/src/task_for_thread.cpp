#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>
#include <unistd.h>

#include "parse_config.hpp"

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responses_map, std::string URL, std::atomic<bool> &status)
{
	std::map<int, unsigned int> status_codes;
	while (status != false)
	{
		std::cout << "Thread works" << std::endl;
		cpr::AsyncResponse async_request = cpr::GetAsync(cpr::Url{URL});
		async_request.wait();
		cpr::Response request = async_request.get();

		if (status_codes.find(request.status_code) != status_codes.end())
		{
			++status_codes[request.status_code];
		}
		else
		{
			status_codes.insert(std::make_pair(request.status_code, 1));
		}
	}

	m.lock();
	for (const auto &entry : status_codes)
	{
		success_responses_map.insert(std::make_pair(entry.first, entry.second));
	}
	m.unlock();
}