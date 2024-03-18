#ifndef TASK_FOR_THREAD_INCLUDE
#define TASK_FOR_THREAD_INCLUDE

#include <mutex>
#include <string>

void task_for_thread(std::mutex &m, int &success_responces, int upper_bound_response, std::string URL);

#endif // TASK_FOR_THREAD_INCLUDE