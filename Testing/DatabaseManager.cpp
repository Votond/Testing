#include "Includes.h"
#include "DatabaseManager.h"

extern sqlite3* db;
extern sqlite3_stmt* stmt;
extern char* error;


int DatabaseManager::getAccountsQuantity()
{
	sqlite3_prepare_v2(db, "SELECT Count(*) FROM users", -1, &stmt, 0);
	sqlite3_step(stmt);
	int quantity = sqlite3_column_int(stmt, 0);

	return quantity;
}


bool DatabaseManager::checkExistence(string login)
{
	string sql = format("SELECT COUNT(*) FROM users WHERE login = {}", SHA256::hashString(login));
	int row_count;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

	if (rc == SQLITE_OK)
	{
		sqlite3_step(stmt);

		if (rc == SQLITE_ROW)
			row_count = sqlite3_column_int(stmt, 0);
	}
	else
	{
		cout << "Sqlite error: " << error;
		return false;
	}

	if (row_count > 0)
		return true;
	else
		return false;
}

bool DatabaseManager::addUser(User user)
{
	string sql = format("INSERT INTO users (fio, address, phone, login, password, user_type) VALUES ({}, {}, {}, {}, {}, {})",
		user.getFio(),
		user.getAddress(),
		user.getPhoneNumber(),
		SHA256::hashString(user.getLogin()),
		SHA256::hashString(user.getPassword()),
		user.getUserType() == User::ADMIN ? "admin" : "tester"
	);

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

	if (rc != SQLITE_OK)
	{
		cout << "Sqlite error: " << error;
		return false;
	}

	return true;
}

bool addUserResult(int user_id, TestResult result)
{

}

pair<bool, User::USER_TYPE> DatabaseManager::validate(string login, string password)
{
	string sql = format("SELECT COUNT(*) FROM users WHERE login = {} AND password = {}",
		SHA256::hashString(login),
		SHA256::hashString(password)
	);
	int row_count;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

	if (rc == SQLITE_OK)
	{
		sqlite3_step(stmt);

		if (rc == SQLITE_ROW)
			row_count = sqlite3_column_int(stmt, 0);
	}
	else
	{
		cout << "Sqlite error: " << error;
	}

	if (row_count > 0)
	{
		string sql = format("SELECT * FROM users WHERE login = {} AND password = {}",
			SHA256::hashString(login),
			SHA256::hashString(password)
		);
		pair<bool, User::USER_TYPE> result;

		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		if (rc == SQLITE_OK)
		{
			sqlite3_step(stmt);

			if (rc == SQLITE_ROW)
			{
				result.first = true;
				result.second = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))) == "admin" ? User::ADMIN : User::TESTER;

				return result;
			}
		}
		else
		{
			cout << "Sqlite error: " << error;

			result.first = false;
			result.second = User::TESTER;

			return result;
		}
	}
	else
	{
		pair<bool, User::USER_TYPE> result;

		result.first = false;
		result.second = User::TESTER;

		return result;
	}
}

vector<string> DatabaseManager::getSections()
{

}

vector<Test> DatabaseManager::getTestsInSection(string section) 
{

}

TestResult DatabaseManager::getUserResult(int user_id, string test_name)
{

}

int DatabaseManager::getUserIdByLogin(string login)
{

}

DatabaseManager::DatabaseManager()
{
	createDatabase();
}

DatabaseManager::~DatabaseManager()
{
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void DatabaseManager::createDatabase()
{
	sqlite3_open("users.db", &db);
	int response = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, fio TEXT, address TEXT, phone TEXT, login TEXT, password TEXT, user_type TEXT)", nullptr, nullptr, &error);

	if (response != SQLITE_OK)
	{
		cout << "Sqlite error: " << error;
	}
}