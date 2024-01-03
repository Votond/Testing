#include "Includes.h"
#include "TestsDatabaseManager.h"
#include "json/json.h"
#include "UserTest.h"
#include "Test.cpp"

class TestsDatabaseManager
{
private:
	string login;
public:
	TestsDatabaseManager(string login) : login(login)
	{
		
	}

	vector<string> getSections()
	{
		Json::Value root = getUserValue();
		vector<string> result;
		auto sections = root["sections"];

		for (Json::Value::iterator it = sections.begin(); it != sections.end(); ++it) {

			string key = it.key().asString();
			result.push_back(key);
		}

		return result;
	}
	

	vector<UserTest> getTestsInSection(string section)
	{
		
	}

	vector<Test> getTestsList()
	{
		
	}
	
	Json::Value getUserValue()
	{
		filesystem::path p{ filesystem::current_path() };
		p = p / "testing" / "users" / (login + ".json");
		ifstream file{ p };
		Json::Value root;

		Json::CharReaderBuilder builder;
		builder["collectComments"] = false;
		string errs;

		parseFromStream(builder, file, &root, &errs);

		return root;
	}
};
