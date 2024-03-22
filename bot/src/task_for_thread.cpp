// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <cpr/cpr.h>

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, std::string URL)
{
	int num_of_requets = 0;
	std::map<int, unsigned int> status_codes;
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
		++num_of_requets;
	} while (num_of_requets != 10);

	m.lock();

	for (const auto &entry : status_codes)
	{
		success_responces_map.insert(std::make_pair(entry.first, entry.second));
	}

	for (const auto &entry : success_responces_map)
	{
		std::cout << entry.first << " : " << entry.second << std::endl;
	}

	m.unlock();

	std::cout << std::endl;
}