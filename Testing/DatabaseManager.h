#pragma once
#include "Includes.h"
#include "sha256/sha256.h"
#include "sqlite/sqlite3.h"
#include "User.h"

class DatabaseManager
{
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	static DatabaseManager instance{};

public:
	static DatabaseManager getInstance() { return instance; }
	// Получение количества аккаунтов
	int getAccountsQuantity();
	// Проверка существования аккаунта по логину
	bool checkExistence(string login);
	bool addUser(User user);
	// Проверка существования аккаунта и его тип по логину и паролю
	pair<bool, User::USER_TYPE> validate(string login, string password);

private:
	DatabaseManager();
	~DatabaseManager();
	void createDatabase();
};
