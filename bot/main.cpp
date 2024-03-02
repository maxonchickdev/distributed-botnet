// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char* argv[]) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/url-to-bot/"}, 
                        cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                        cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    std::cout << r.status_code << std::endl;
    std::cout << r.header["content-type"] << std::endl;
    std::cout << r.text << std::endl;

    return 0;
}
