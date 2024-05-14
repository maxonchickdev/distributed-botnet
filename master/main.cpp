// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cpr/cpr.h>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>

#include "db_methods.hpp"
#include "status_codes_db_methods.hpp"

int main()
{
    std::mutex m;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *path_to_db = "./data/demo.db";

    sqlite3 *db_codes;
    sqlite3_stmt *stmt_codes;
    const char *path_to_res_db = "./data/res.db";

    std::vector<std::string> data;
    std::vector<std::string> res_data;
    std::string bots_state;
    // std::string getting_data;

    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();

    cors
        .global()
        .headers("*")
        .methods("POST"_method, "GET"_method)
        .prefix("/cors")
        .origin("http://localhost:5173");

    CROW_ROUTE(app, "/")
        .methods("GET"_method)([]()
                               { return "Welcome to master structure"; });

    CROW_ROUTE(app, "/url-to-db/")
        .methods("POST"_method)([&db, &stmt, path_to_db](const crow::request &req)
                                {
            __connect_to_db(db, stmt, path_to_db);
            const auto response_url = req.body;
            __push_to_db(db, stmt, response_url, path_to_db);
            return response_url; });

    CROW_ROUTE(app, "/get-url-from-db/").methods("GET"_method)([&]()
                                                               {
            __get_from_db(db, stmt, data, path_to_db);
            return data.back(); });

    CROW_ROUTE(app, "/recive-bot-state/").methods("POST"_method)([&](const crow::request &req)
                                                                 {
            bots_state = req.body;
            return bots_state; });

    CROW_ROUTE(app, "/push-bot-state/").methods("GET"_method)([&]()
                                                              { return bots_state; });

    CROW_ROUTE(app, "/recive-data/").methods("POST"_method)([&](const crow::request &req)
                                                            {
        __connect_to_db_status_codes(db_codes, stmt_codes, path_to_res_db);
        m.lock();
        const auto response_data = req.body;
        std::cout << response_data << std::endl;
        // getting_data = response_data;
        // size_t index = getting_data.find('&');
        // if(index != std::string::npos) std::cout << index << std::endl;
        __push_to_db_status_codes(db_codes, stmt_codes, response_data, path_to_res_db);
        m.unlock();
        // std::cout << getting_data << std::endl;
        return "Data received"; });

    CROW_ROUTE(app, "/getting-data/").methods("GET"_method)([&]()
                                                            {
        __get_from_db_status_codes(db_codes, stmt_codes, res_data, path_to_res_db);
        return res_data.back(); });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}
