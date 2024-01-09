#pragma once
#include "Includes.h"
#include "Test.h"
#include "TestResult.h"

class TesterArea
{
	static TesterArea instance{};

public:
	static TesterArea getInstance();
	void start(string login);
	void chooseTest(string login);
	void chooseResult(string login);
	void startTest(int id);
	void viewResult(int id);
	void printSections(vector<string> sections);
	void printTests(vector<Test> tests);
	Test getTestByName(vector<Test> tests, string name);
	void printTestResult(TestResult result);
};
