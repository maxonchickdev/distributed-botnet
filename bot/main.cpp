// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <mutex>
#include <map>
#include <cpr/cpr.h>

#include "managing_threads.hpp"
#include "task_for_thread.hpp"
#include "parse_config.hpp"

int main(int argc, char *argv[])
{
    const std::string path_to_cfg = "./data/config.cfg";
    std::map<std::string, std::string> config_map = parse_config(path_to_cfg);

    const std::string get_target = config_map["get_target"];
    const std::string num_of_threads = config_map["num_of_threads"];

    const cpr::Response r = cpr::Get(cpr::Url{get_target});

    const std::string URL = r.text;

    std::cout << "Terget: " << URL << std::endl
              << "Number of threads: " << num_of_threads << std::endl;
    ;

    cpr::Response connect = cpr::Post(cpr::Url{"http://localhost:8080/connect/"});
    do
    {
        if (connect.text == "Pick me!")
        {
            managind_threads(task_for_thread, std::stod(num_of_threads), URL);
        }
    } while (true);

    return 0;
}
