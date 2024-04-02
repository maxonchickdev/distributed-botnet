#ifndef TASK_FOR_THREAD_INCLUDE
#define TASK_FOR_THREAD_INCLUDE

#include <mutex>
#include <string>
#include <map>

void task_for_thread(std::mutex &m, std::map<int, unsigned int> &success_responces_map, std::string URL, std::atomic<bool> &status);

#endif // TASK_FOR_THREAD_INCLUDE