#pragma once
#include "Includes.h"
#include "Test.h"
#include "TestResult.h"
#include "DatabaseManager.h"

class TesterArea
{
	static TesterArea instance;

public:
	static TesterArea getInstance() { return instance; };
	void start(string login);
	void chooseTest(string login);
	void chooseResult(string login);
	void printSections(vector<pair<int, string>> sections);
	void printTests(vector<Test> tests);
	Test getTestByName(vector<Test> tests, string name);
	void printTestResult(TestResult result);
};
