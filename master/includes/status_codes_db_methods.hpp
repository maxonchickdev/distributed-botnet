#ifndef STATUS_CODES_DB_METHODS_INCLUDE
#define STATUS_CODES_DB_METHODS_INCLUDE

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

void __connect_to_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, const char *path_to_db);
void __push_to_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, const std::string status_code, const char *path_to_db);
void __get_from_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, std::vector<std::string> &data, const char *path_to_db);

#endif // STATUS_CODES_DB_METHODS_INCLUDE