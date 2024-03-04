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
    std::cout << r.status_code << std::endl;

    int counter = 0;

    for(int i = 0; i < 10; ++i) {
        cpr::Response target_r = cpr::Get(cpr::Url{URL});
        if(target_r.status_code != 200) {
            break;
        }
        ++counter;
        std::cout << "request " << i << " sending successfully" << std::endl;
    }

    std::cout << counter << std::endl;

    return 0;
}
