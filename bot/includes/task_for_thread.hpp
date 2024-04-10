#ifndef TASK_FOR_THREAD_INCLUDE
#define TASK_FOR_THREAD_INCLUDE

#include <mutex>
#include <string>
#include <map>
#include <cpr/cpr.h>

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, cpr::Url URL, std::atomic<bool> &status);

#endif // TASK_FOR_THREAD_INCLUDE