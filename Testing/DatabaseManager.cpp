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
	string sql = format("INSERT INTO results (user_id, test_id, correct, incorrect) VALUES ({}, {}, {}, {})",
		user_id,
		result.getTestId(),
		result.getCorrect(),
		result.getIncorrect()
	);

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

	if (rc != SQLITE_OK)
	{
		cout << "Sqlite error: " << error;
		return false;
	}

	return true;
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

		row_count = sqlite3_column_int(stmt, 0);
	}
	else
	{
		cout << "Sqlite error: " << error;
	}

	if (row_count > 0)
	{
		sql = format("SELECT * FROM users WHERE login = {} AND password = {}",
			SHA256::hashString(login),
			SHA256::hashString(password)
		);
		pair<bool, User::USER_TYPE> result;

		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

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

			return {false, User::TESTER};
		}
	}
	else
	{
		return {false, User::TESTER};
	}
}

vector<pair<int, string>> DatabaseManager::getSections()
{
	string sql = "SELECT * FROM sections";
	vector<pair<int, string>> result;

	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			pair<int, string> pair;
			pair.first = sqlite3_column_int(stmt, 0);
			pair.second = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

			result.push_back(pair);
		}

		return result;
	}
	else
	{
		cout << "Sqlite error: " << error;
		return {};
	}
}

vector<Test::Question> DatabaseManager::getQuestionsForTest(int test_id)
{//id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT, answers TEXT, right_answer TEXT, test_id INTEGER
	string sql = "SELECT * FROM questions WHERE test";
	vector<Test::Question> result;
	
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			vector<string> splitted_answers;
			string answers = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

			{
				// string split

				std::stringstream ss(answers);
				std::string item;

				while (std::getline(ss, item, ';')) {
					splitted_answers.push_back(item);
				}
			}

			result.push_back(Test::Question(
				string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
				splitted_answers, 
				string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)))
			));
		}

		return result;
	}
	else
	{
		cout << "Sqlite error: " << error;
		return {};
	}
}

int DatabaseManager::getSectionByName(string name)
{
	sqlite3_prepare_v2(db, format("SELECT id FROM sections WHERE name = {}", name).c_str(), -1, &stmt, 0);
	sqlite3_step(stmt);
	int id = sqlite3_column_int(stmt, 0);

	return id;
}

Test DatabaseManager::getTestByName(string name)
{//id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, section_id INTEGER, question_id INT
	sqlite3_prepare_v2(db, format("SELECT * FROM tests WHERE name = {}", name).c_str(), -1, &stmt, 0);
	sqlite3_step(stmt);
	string section_name = "";
	int id = sqlite3_column_int(stmt, 0);

	for (pair<int, string> section : getSections())
	{
		if (section.first == sqlite3_column_int(stmt, 2))
		{
			section_name = section.second;
			break;
		}
	}
	
	return Test(id,
		section_name,
		string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
		getQuestionsForTest(id)
	);
}

vector<Test> DatabaseManager::getTestsInSection(string section)
{//id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, section_id INTEGER
	string sql = format("SELECT name FROM tests WHERE section_id = {}", getSectionByName(section));
	vector<Test> result;

	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			result.push_back(getTestByName(string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))));
		}

		return result;
	}
	else
	{
		cout << "Sqlite error: " << error;
		return {};
	}
}

TestResult DatabaseManager::getUserResult(int user_id, string test_name)
{//id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, test_id INTEGER, correct INTEGER, incorrect INTEGER
	sqlite3_prepare_v2(db, format("SELECT (test_id, correct, incorrect) FROM results WHERE user_id = {} AND test_id = {}", user_id, getTestByName(test_name).getId()).c_str(), -1, &stmt, 0);
	sqlite3_step(stmt);
	int test_id = sqlite3_column_int(stmt, 0);
	int correct = sqlite3_column_int(stmt, 1);
	int incorrect = sqlite3_column_int(stmt, 2);

	return TestResult(test_id, correct, incorrect);
}

int DatabaseManager::getUserIdByLogin(string login)
{//id INTEGER PRIMARY KEY AUTOINCREMENT, fio TEXT, address TEXT, phone TEXT, login TEXT, password TEXT, user_type TEXT
	sqlite3_prepare_v2(db, format("SELECT id FROM users WHERE login = {}", SHA256::hashString(login)).c_str(), -1, &stmt, 0);
	sqlite3_step(stmt);
	int id = sqlite3_column_int(stmt, 0);

	return id;
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
	vector<string> sql
	{
		"CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY AUTOINCREMENT, fio TEXT, address TEXT, phone TEXT, login TEXT, password TEXT, user_type TEXT)",
		"CREATE TABLE IF NOT EXISTS tests(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, section_id INTEGER)",
		"CREATE TABLE IF NOT EXISTS questions(id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT, answers TEXT, right_answer TEXT, test_id INTEGER)", // answers separated by ; e.g. 3;6;1;8;
		"CREATE TABLE IF NOT EXISTS sections(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)",
		"CREATE TABLE IF NOT EXISTS results(id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, test_id INTEGER, correct INTEGER, incorrect INTEGER)"
	};

	for (string st : sql)
	{
		int response = sqlite3_exec(db, st.c_str(), nullptr, nullptr, &error);

		if (response != SQLITE_OK)
		{
			cout << "Sqlite error: " << error;
		}
	}
}