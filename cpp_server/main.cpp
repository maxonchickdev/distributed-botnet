// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>


#include "crow.h"
#include "crow/middlewares/cors.h"
// #include "./include/cpr/cpr.h"


int main() {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
      .global().headers("Origin", "Content-Type", "Accept", "*").methods("POST"_method, "GET"_method).prefix("/cors").origin("example.com").prefix("/nocors").ignore();

    CROW_ROUTE(app, "/")([](){
        return "Maxondevelop";
    });

    CROW_ROUTE(app, "/hello/<int>")([](int count){
        return crow::response(std::to_string(count));
    });

    app.port(8080)
    .multithreaded()
    .run();

    return 0;
}
