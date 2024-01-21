#pragma once
#include "Includes.h"
#include "sha256/sha256.h"
#include "sqlite/sqlite3.h"
#include "User.h"
#include "TestResult.h"

class DatabaseManager
{
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	static DatabaseManager instance;

public:
	static DatabaseManager getInstance() { return instance; }
	// Получение количества аккаунтов
	int getAccountsQuantity();
	// Проверка существования аккаунта по логину
	bool checkExistence(string login);
	bool addUser(User user);
	bool addUserResult(int user_id, TestResult result);
	// Проверка существования аккаунта и его тип по логину и паролю
	pair<bool, User::USER_TYPE> validate(string login, string password);
	vector<pair<int, string>> getSections();
	vector<Test::Question> getQuestionsForTest(int test_id);
	int getSectionByName(string name);
	Test getTestByName(string name);
	vector<Test> getTestsInSection(string section);
	TestResult getUserResult(int user_id, string test_name);
	int getUserIdByLogin(string login);

	DatabaseManager();
	~DatabaseManager();
	void createDatabase();
};
