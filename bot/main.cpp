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
#include <cpr/cpr.h>
#include <thread>


/**
 * @brief Main method
 * 
 * @param argc Number of params wich users using in CLI
 * @param argv All params wich users using in CLI
 * @return int 
 */

int main(int argc, char* argv[]) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/url-to-bot/"});

    std::string URL = r.text;

    std::cout << URL << std::endl;

    int counter = 0;

    for(int i = 0; i < 50; ++i) {
        int wrap_counter = 0;
        std::thread t([&URL, &counter, &i, &wrap_counter]() {
            for(int j = 0; j < 100; ++j) {
                cpr::Response target_r = cpr::Get(cpr::Url{URL});
                if(target_r.status_code != 200) {
                    break;
                }
                ++wrap_counter;
                std::cout << "request " << j << " sending successfully " << ", thread " << i << std::endl;
            }
            counter += wrap_counter;
        });
        t.join();
    }

    std::cout << counter << std::endl;

    return 0;
}
