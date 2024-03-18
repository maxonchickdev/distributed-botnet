// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

/**
 * @file main.cpp
 * @author your name (kutsenko.pn@ucu.edu.ua)
 * @brief This file handles bot wich sending requests
 * @version 0.1
 * @date 2024-03-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <string>
#include <mutex>
#include <cpr/cpr.h>

#include "managing_threads.hpp"
#include "task_for_thread.hpp"

/**
 * @brief Main method
 *
 * @param argc Number of params wich users using in CLI
 * @param argv All params wich users using in CLI
 * @return int
 */

int main(int argc, char *argv[])
{
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/url-to-bot/"});

    std::string URL = r.text;

    std::cout << URL << std::endl;

    int num_of_threads = 4;
    int num_of_requests = 50;

    int final_result = managind_threads(task_for_thread, num_of_threads, num_of_requests, URL);

    std::cout << final_result << std::endl;

    return 0;
}
