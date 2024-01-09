#include "TesterArea.h"

#include "Test.h"

extern static TesterArea instance();

TesterArea TesterArea::getInstance()
{
	return instance;
}

void TesterArea::start(string login)
{
	int action;

	cout << "Выберите действие:\n1 - Просмотр результатов тестов\n2 - Прохождение теста\n";
	cin >> action;

	switch (action)
	{
	case 1:
		chooseResult(login);
		break;

	case 2:
		chooseTest(login);
		break;
	}
}

void TesterArea::chooseTest(string login)
{
	
}

void TesterArea::chooseResult(string login)
{
	string section;
	string name;
	TestsDatabaseManager tests_manager(login);
	vector<string> sections = tests_manager.getSections();
	vector<Test> tests;

	printSections(sections);

	cout << "Введите название нужного раздела: ";
	cin >> section;

	tests = tests_manager.getTestsInSection(section);

	printTests(tests);

	cout << "Введите название нужного теста: ";
	cin >> name;

	Test test = getTestByName(tests, name);

	cout << "| Название: " << test.getName() << endl;
	cout << "| Раздел: " << test.getSection() << endl;
	cout << "| Результат:\n";
	printTestResult(test.getResult());

	start(login);

	throw "need rework";
}

void TesterArea::startTest(int id)
{
	
}

void TesterArea::viewResult(int id)
{


}

void TesterArea::printSections(vector<string> sections)
{
	for (string section : sections)
	{
		cout << format("~~~~~~~~* {} *~~~~~~~~\n", section);
	}
}

void TesterArea::printTests(vector<UserTest> tests)
{
	for (UserTest test : tests)
	{
		cout << format("--------* {} *--------\n", test.getName());
	}
}

UserTest TesterArea::getTestByName(vector<UserTest> tests, string name)
{
	for (UserTest test : tests)
	{
		if (test.getName() == name)
		{
			return test;
		}
	}
}

void TesterArea::printTestResult(TestResult result)
{
	cout << "| Правильные ответы: " << result.getCorrect() << endl;
	cout << "| Неправильные ответы: " << result.getIncorrect() << endl;
	cout << "| Процент правильных ответов: " << result.getCorrectPerc() << endl;
	cout << "| Процент неправильных ответов: " << result.getIncorrectPerc() << endl;
	cout << "| Оценка: " << result.getMark() << endl;
}