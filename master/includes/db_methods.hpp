#ifndef DB_INCLUDE
#define DB_INCLUDE

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

void __connect_to_db(sqlite3 *db, sqlite3_stmt *stmt, const char *path_to_db);
void __push_to_db(sqlite3 *db, sqlite3_stmt *stmt, const std::string URL, const char *path_to_db);
void __get_from_db(sqlite3 *db, sqlite3_stmt *stmt, std::vector<std::string> &data, const char *path_to_db);

#endif // DB_INCLUDE