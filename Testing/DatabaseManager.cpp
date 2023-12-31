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
		
	}

	bool checkExistence(string login)
	{
		
	}

	void addUser(User user)
	{
		
	}

	pair<bool, User::USER_TYPE> validate(string login, string password)
	{
		
	}

private:
	DatabaseManager()
	{
		createDatabase();
	}

	void createDatabase()
	{
		sqlite3_open("users.db", &db);
		int response = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(test INT)", nullptr, nullptr, &error);

		if (response != SQLITE_OK)
		{
			cout << "Sqlite error: " << error;
		}
	}
};
