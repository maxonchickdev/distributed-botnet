// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <cpr/cpr.h>

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
