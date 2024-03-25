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
    const std::string num_of_threads = config_map["num_of_threads"];
    const std::string connect = config_map["connect"];
    std::string get_target = config_map["get_target"];
    cpr::Response connect_status = cpr::Post(cpr::Url{connect});

    do
    {
        connect_status = cpr::Post(cpr::Url{connect});
        std::cout << "Status code: " << connect_status.status_code;
    } while (connect_status.text != "true");

    const cpr::Response target = cpr::Get(cpr::Url{get_target});
    managind_threads(task_for_thread, std::stod(num_of_threads), target.text);

    return 0;
}
