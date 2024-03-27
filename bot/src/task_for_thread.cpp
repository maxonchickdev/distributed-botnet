// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>
#include <unistd.h>

#include "parse_config.hpp"

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, std::string URL, bool &status)
{
	std::map<int, unsigned int> status_codes;
	while (status != false)
	{
		std::cout << "Threads works" << std::endl;
		cpr::Response request = cpr::Get(cpr::Url{URL});
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
		success_responces_map.insert(std::make_pair(entry.first, entry.second));
	}

	m.unlock();
}