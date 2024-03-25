// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, std::string URL)
{
	std::map<int, unsigned int> status_codes;
	int bound = 0;
	do
	{
		do
		{
			cpr::Response request = cpr::Get(cpr::Url{URL});
			if (status_codes.find(request.status_code) != status_codes.end())
			{
				++status_codes[request.status_code];
			}
			else
			{
				status_codes.insert(std::make_pair(request.status_code, 1));
			}
			++bound;
		} while (bound != 10);

		bound = 0;

		m.lock();

		for (const auto &entry : status_codes)
		{
			success_responces_map.insert(std::make_pair(entry.first, entry.second));
		}

		std::vector<cpr::Pair> payload_data;
		for (const auto &entry : success_responces_map)
		{
			payload_data.push_back(cpr::Pair{std::to_string(entry.first), std::to_string(entry.second)});
		}
		cpr::Payload payload{payload_data.begin(), payload_data.end()};
		cpr::Response post_to_masetr = cpr::Post(cpr::Url{"http://localhost:8080/data/"}, payload);
		std::cout << post_to_masetr.status_code << std::endl;

		m.unlock();
	} while (true);
}