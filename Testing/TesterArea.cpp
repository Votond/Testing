﻿#include "Includes.h"
#include "TesterArea.h"
#include "json/json.h"
#include "TestsDatabaseManager.cpp"

class TesterArea
{
	static TesterArea instance();

public:
	static TesterArea getInstance()
	{
		return instance();
	}

	void start()
	{
		int action;

		cout << "Выберите действие:\n1 - Просмотр результатов тестов\n2 - Прохождение теста\n";
		cin >> action;

		switch (action)
		{
		case 1:
			chooseResult();
			break;

		case 2:
			chooseTest();
			break;
		}
	}

	void chooseTest()
	{
		
	}

	void chooseResult()
	{
		string section;
		string name;
		vector<string> sections = TestsDatabaseManager::getInstance().getSections();
		vector<UserTest> tests;

		printSections(sections);

		cout << "Введите название нужного раздела: ";
		cin >> section;

		tests = TestsDatabaseManager::getInstance().getTestsInSection(section);

		printTests(tests);

		cout << "Введите название нужного теста: ";
		cin >> name;

		UserTest test = getTestByName(tests, name);

		cout << "| Название: " << test.getName() << endl;
		cout << "| Раздел: " << test.getSection() << endl;
		cout << "| Результат:\n";
		printTestResult(test.getResult());

		start();
	}

	void startTest(int id)
	{
		
	}

	void viewResult(int id)
	{


	}

	void printSections(vector<string> sections)
	{
		for (string section : sections)
		{
			cout << format("~~~~~~~~* {} *~~~~~~~~\n", section);
		}
	}

	void printTests(vector<UserTest> tests)
	{
		for (UserTest test : tests)
		{
			cout << format("--------* {} *--------\n", test.getName());
		}
	}

	UserTest getTestByName(vector<UserTest> tests, string name)
	{
		for (UserTest test : tests)
		{
			if (test.getName() == name)
			{
				return test;
			}
		}
	}

	void printTestResult(TestResult result)
	{
		cout << "| Правильные ответы: " << result.getCorrect() << endl;
		cout << "| Неправильные ответы: " << result.getIncorrect() << endl;
		cout << "| Процент правильных ответов: " << result.getCorrectPerc() << endl;
		cout << "| Процент неправильных ответов: " << result.getIncorrectPerc() << endl;
		cout << "| Оценка: " << result.getMark() << endl;
	}
};