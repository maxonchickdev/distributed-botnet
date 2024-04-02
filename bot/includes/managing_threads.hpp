#ifndef MANAGING_THREADS_INCLUDE
#define MANAGING_THREADS_INCLUDE

#include <mutex>
#include <thread>
#include <string>
#include <map>

template <typename TASK_FOR_THREAD>
std::map<int, unsigned int> managind_threads(TASK_FOR_THREAD worker, int num_of_workers, std::string URL, std::atomic<bool> &status)
{
	std::map<int, unsigned int> status_codes;
	std::mutex m;
	std::vector<std::thread> workers;

	for (int i = 0; i < num_of_workers; ++i)
	{
		workers.emplace_back(worker, std::ref(m), std::ref(status_codes), std::ref(URL), std::ref(status));
	}

	for (int i = 0; i < workers.size(); ++i)
	{
		workers[i].join();
	}

	std::vector<cpr::Pair> payload_data;
	for (const auto &entry : status_codes)
	{
		payload_data.push_back(cpr::Pair{std::to_string(entry.first), std::to_string(entry.second)});
	}
	cpr::Payload payload{payload_data.begin(), payload_data.end()};
	cpr::Response post_to_masetr = cpr::Post(cpr::Url{"http://localhost:8080/recive-data/"}, payload);
	std::cout << post_to_masetr.status_code << std::endl;

	return status_codes;
}

#endif // MANAGING_THREADS_INCLUDE