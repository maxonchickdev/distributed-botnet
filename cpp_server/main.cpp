// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cpr/cpr.h>
#include <sqlite3.h>


void connection(sqlite3* db, sqlite3_stmt* stmt) {
    int res_connecting;
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {
        res_connecting = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(name varchar(50), roll INT, email varchar(80));", 0, 0, 0);
        
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

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    connection(db, stmt);

    sqlite3_close(db);

    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Origin", "Content-Type", "Accept", "*")
        .methods("POST"_method, "GET"_method)
        .prefix("/cors")
        .origin("example.com")
        .prefix("/nocors")
        .ignore();

    CROW_ROUTE(app, "/") ([]() {
        cpr::Response r = cpr::Get(cpr::Url{"https://65df88a5ff5e305f32a26bdf.mockapi.io/destination/elements/"});
        std::cout << r.text << std::endl;
        return "Maxondevelop"; 
    });

    CROW_ROUTE(app, "/hello/<int>") ([](int count) { 
        return crow::response(std::to_string(count));
    });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}