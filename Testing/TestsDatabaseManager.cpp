#include "Includes.h"
#include "TestsDatabaseManager.h"
#include "json/json.h"

class TestsDatabaseManager
{
public:
	static TestsDatabaseManager instance();

public:
	static TestsDatabaseManager getInstance()
	{
		return instance();
	}

	vector<string> getSections()
	{
		
	}

	vector<Test> getTestsInSection(string section)
	{
		
	}
};
