#ifndef MANAGING_THREADS_INCLUDE
#define MANAGING_THREADS_INCLUDE

#include <mutex>
#include <thread>
#include <string>

template <typename TASK_FOR_THREAD>
int managind_threads(TASK_FOR_THREAD worker, int num_of_workers, int num_of_requests, std::string URL)
{
	int successfully = 0;
	std::mutex m;
	std::vector<std::thread> workers;

	for (int i = 0; i < num_of_workers; ++i)
	{
		workers.emplace_back(worker, std::ref(m), std::ref(successfully), std::ref(num_of_requests), std::ref(URL));
	}

	for (int i = 0; i < workers.size(); ++i)
	{
		workers[i].join();
	}

	return successfully;
}

#endif // MANAGING_THREADS_INCLUDE