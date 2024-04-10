#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>
#include <unistd.h>

#include "parse_config.hpp"

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responses_map, cpr::Url URL, std::atomic<bool> &status)
{

	while (status != false)
	{
		std::vector<cpr::AsyncResponse> container{};
		for (int i = 0; i < 100; ++i)
		{
			container.emplace_back(cpr::GetAsync(URL, cpr::Parameters{{"i", std::to_string(i)}}));
		}

		m.lock();
		for (cpr::AsyncResponse &ar : container)
		{
			cpr::Response r = ar.get();
			if (success_responses_map.find(r.status_code) != success_responses_map.end())
				++success_responses_map[r.status_code];
			else
				success_responses_map[r.status_code] = 1;
		}
		std::vector<cpr::Pair> payload_data;
		for (const auto &el : success_responses_map)
		{
			payload_data.push_back(cpr::Pair{std::to_string(el.first), std::to_string(el.second)});
		}
		cpr::Payload payload{payload_data.begin(), payload_data.end()};
		cpr::Response post_to_master = cpr::Post(cpr::Url{"http://localhost:8080/recive-data/"}, payload);
		success_responses_map.clear();
		m.unlock();
	}
}