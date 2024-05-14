#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

void __connect_to_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, const char *path_to_db)
{
	const char *query = "CREATE TABLE IF NOT EXISTS status_codes(id INTEGER PRIMARY KEY AUTOINCREMENT, status_code VARCHAR(80));";
	if (sqlite3_open(path_to_db, &db) == SQLITE_OK)
	{
		sqlite3_prepare(db, query, -1, &stmt, NULL);
		sqlite3_step(stmt);
	}
	else
	{
		std::cerr << "Faild to open db" << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void __push_to_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, const std::string status_code, const char *path_to_db)
{
	const std::string query = "INSERT INTO status_codes (status_code) VALUES ('" + status_code + "');";
	if (sqlite3_open(path_to_db, &db) == SQLITE_OK)
	{
		sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
	}
	else
	{
		std::cerr << "Faild to open db" << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void __get_from_db_status_codes(sqlite3 *db, sqlite3_stmt *stmt, std::vector<std::string> &data, const char *path_to_db)
{
	const std::string query = "SELECT status_code FROM status_codes;";
	if (sqlite3_open(path_to_db, &db) == SQLITE_OK)
	{
		if (sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK)
		{
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				const unsigned char *url = sqlite3_column_text(stmt, 0);
				data.push_back(std::string(reinterpret_cast<const char *>(url)));
			}
		}
		else
		{
			std::cerr << "Failed to prepare query" << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to open db" << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}