#include "Includes.h"
#include "UserTest.h"
#include "TestResult.cpp"

// Тест, пройденный пользователем
class UserTest
{
private:
	string section;
	string name;
	TestResult result;

public:
	UserTest(string section, string name, int correct, int incorrect) : section(section), name(name), result(TestResult(correct, incorrect))
	{

	}

	string getSection() { return section; }
	string getName() { return name; }
	TestResult getResult() { return result; }
};