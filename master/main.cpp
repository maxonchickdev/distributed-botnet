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

#include "db_methods.hpp"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *path_to_db = "./data/demo.db";
    std::vector<std::string> data;
    std::string bots_state;

    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();

    std::string getting_data;

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
        const auto response_data = req.body;
        getting_data = response_data;
        std::cout << response_data << std::endl;
        return getting_data; });

    // CROW_WEBSOCKET_ROUTE(app, "/ws")
    //     .onopen([&](crow::websocket::connection &conn)
    //             { return "connected"; })
    //     .onclose([&](crow::websocket::connection &conn, const std::string &reason)
    //              { return "disconnected"; })
    //     .onmessage([&](crow::websocket::connection &conn, const std::string &data, bool is_binary)
    //                { return getting_data; });

    CROW_ROUTE(app, "/getting-data/").methods("GET"_method)([&]()
                                                            { return getting_data; });

    // CROW_ROUTE(app, "/get-library/<string>").methods("GET"_method)([](const crow::request &req, std::string dylib_name)
    //                                                                {
    //     std::string dylib_path = "./so_lib/build/" + dylib_name;
    //     std::ifstream infile(dylib_path, std::ifstream::binary);
    //     std::ostringstream oss;
    //     oss << infile.rdbuf();
    //     std::cout << dylib_path << std::endl << oss.str() << std::endl;
    //     crow::response response(200, "application/octet-stream", oss.str());
    //     response.set_header("Content-Disposition", "attachment; filename=" + dylib_name);
    //     return response; });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}
