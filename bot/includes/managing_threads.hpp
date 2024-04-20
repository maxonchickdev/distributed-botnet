#ifndef MANAGING_THREADS_INCLUDE
#define MANAGING_THREADS_INCLUDE

#include <mutex>
#include <thread>
#include <string>
#include <map>
#include <unistd.h>
#include <cpr/cpr.h>

template <typename TASK_FOR_THREAD>
std::map<int, unsigned int> managind_threads(TASK_FOR_THREAD worker, int num_of_workers, cpr::Url URL, std::atomic<bool> &status, const unsigned int requests_per_post)
{
	std::map<int, unsigned int> status_codes;
	std::mutex m;
	std::vector<std::thread> workers;

	for (int i = 0; i < num_of_workers; ++i)
	{
		workers.emplace_back(worker, std::ref(m), std::ref(status_codes), std::ref(URL), std::ref(status), std::ref(requests_per_post));
	}

	for (int i = 0; i < workers.size(); ++i)
	{
		workers[i].join();
	}

	return status_codes;
}

#endif // MANAGING_THREADS_INCLUDE