// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>

#include <crow.h>
#include <cpr/cpr.h>


int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });
    CROW_ROUTE(app, "/hello/<int>")([](int count){
        return crow::response(std::to_string(count));
    });
    app.port(8080)
    .multithreaded()
    .run();
    return 0;
}
