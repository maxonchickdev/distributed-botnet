// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cpr/cpr.h>
#include <sqlite3.h>
#include <string>
#include <vector>


void connection_to_db(sqlite3 *db, sqlite3_stmt *stmt) {
    int res_connecting;
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {
        res_connecting = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS urls(id INTEGER PRIMARY KEY AUTOINCREMENT, url TEXT);", nullptr, nullptr, nullptr);
        
        if (res_connecting != SQLITE_OK) {
            std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Table created successfully" << std::endl;
        }
        
        sqlite3_close(db);
    }
    else {
        std::cerr << "Failed to open database." << std::endl;
    }
}

void push_url_to_db(sqlite3 *db, sqlite3_stmt *stmt, std::string url) {
    std::string sqlite3_statement = "INSERT INTO urls(url) VALUES ('" + url + "')";
    if(sqlite3_open("demo.db", &db) == SQLITE_OK) {
        sqlite3_prepare(db, sqlite3_statement.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
    } else {
        std::cerr << "Faild to open db" << std::endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

std::vector<std::string> get_url_from_db(sqlite3 *db, sqlite3_stmt *stmt) {
    std::vector<std::string> urls;
    std::string sqlite3_data = "SELECT * FROM urls;";

    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {
        if (sqlite3_prepare(db, sqlite3_data.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                const unsigned char *url = sqlite3_column_text(stmt, 1);
                urls.push_back(reinterpret_cast<const char *>(url));
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open db" << std::endl;
    }
    return urls;
}

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    connection_to_db(db, stmt);

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
        return "Hello, bro";
    });

    CROW_ROUTE(app, "/get-url/").methods("POST"_method)
    ([&db, &stmt](const crow::request &req)
    {
        std::string response_url = req.body;
        push_url_to_db(db, stmt, response_url);
        std::cout << response_url << std::endl;
        return response_url;
    });

    CROW_ROUTE(app, "/url-to-bot/").methods("GET"_method)
    ([&db, &stmt]() {
        std::vector<std::string> response_data = get_url_from_db(db, stmt);
        for(const auto &el: response_data) {
            std::cout << el << std::endl;
        }
        return response_data.back();
    });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}
