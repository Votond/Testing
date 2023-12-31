#include "Includes.h"
#include "DatabaseManager.h"
#include "sha256/sha256.h"
#include "sqlite/sqlite3.h"
#include "User.cpp"

class DatabaseManager
{
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	static DatabaseManager instance();

public:
	static DatabaseManager getInstance()
	{
		return instance();
	}

	long getAccountsQuantity()
	{
		sqlite3_prepare_v2(db, "SELECT Count(*) FROM users", -1, &stmt, 0);
		sqlite3_step(stmt);
		long quantity = sqlite3_column_int64(stmt, 0);

		return quantity;
	}

	bool checkExistence(string login)
	{
		sqlite3_prepare_v2(db, "SELECT EXISTS(SELECT * FROM Reps WHERE UserId = % s) AS bool", -1, &stmt, 0);
		sqlite3_step(stmt);
		bool quantity = sqlite3_column_blob(stmt, 0);

		return quantity;
	}

	void addUser(User user)
	{
		string sql = format("INSERT INTO users (fio, address, phone, login, password, user_type) VALUES ({}, {}, {}, {}, {}, {})", user.getFio(), user.getAddress(), user.getPhoneNumber(), SHA256::hashString(user.getLogin()), SHA256::hashString(user.getPassword()), user.getUserType() == User::ADMIN ? "admin" : "tester");

		int response = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

		if (response != SQLITE_OK)
		{
			cout << "Sqlite error: " << error;
		}
	}

	pair<bool, User::USER_TYPE> validate(string login, string password)
	{
		int response = sqlite3_exec(db, "", nullptr, nullptr, &error);

		if (response != SQLITE_OK)
		{
			cout << "Sqlite error: " << error;
		}
	}

private:
	DatabaseManager()
	{
		createDatabase();
	}

	void createDatabase()
	{
		sqlite3_open("users.db", &db);
		int response = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, fio TEXT, address TEXT, phone TEXT, login TEXT, password TEXT, user_type TEXT)", nullptr, nullptr, &error);

		if (response != SQLITE_OK)
		{
			cout << "Sqlite error: " << error;
		}
	}
};
