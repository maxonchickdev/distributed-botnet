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
	int counter = 0;

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
		++counter;

		if (counter == 10)
		{
			m.lock();
			for (const auto &entry : status_codes)
			{
				success_responses_map.insert(std::make_pair(entry.first, entry.second));
			}
			std::vector<cpr::Pair> payload_data;
			for (const auto &el : success_responses_map)
			{
				payload_data.push_back(cpr::Pair{std::to_string(el.first), std::to_string(el.second)});
			}
			cpr::Payload payload{payload_data.begin(), payload_data.end()};
			cpr::Response post_to_master = cpr::Post(cpr::Url{"http://localhost:8080/recive-data/"}, payload);
			m.unlock();

			counter = 0;
			status_codes.clear();
		}
	}
}