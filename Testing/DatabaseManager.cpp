#include "Includes.h"
#include "DatabaseManager.h"

#include "sha256.h"
#include "User.cpp"

class DatabaseManager
{
private:
	static DatabaseManager instance();

public:
	static DatabaseManager getInstance()
	{
		return instance();
	}

	long getAccountsQuantity()
	{
		
	}

	bool checkExistence(string login, string password)
	{
		
	}

	void addUser(User user)
	{
		
	}

private:
	DatabaseManager()
	{
		createDatabase();
	}

	void createDatabase()
	{
		
	}
};
