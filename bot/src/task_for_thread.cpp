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

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, std::string URL)
{
	const std::string path_to_cfg = "./data/config.cfg";
	std::map<std::string, std::string> config_map = parse_config(path_to_cfg);
	const std::string connect = config_map["connect"];
	cpr::Response connect_status = cpr::Get(cpr::Url{connect});

	std::map<int, unsigned int> status_codes;
	while (connect_status.text == "true")
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

		cpr::Response r = cpr::Get(cpr::Url{connect});
		connect_status.text = r.text;
		sleep(5);
	}

	m.lock();

	for (const auto &entry : status_codes)
	{
		success_responces_map.insert(std::make_pair(entry.first, entry.second));
	}

	m.unlock();
}