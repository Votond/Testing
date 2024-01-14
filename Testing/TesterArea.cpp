#include "TesterArea.h"

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
	string section;
	string test_name;
	int counter = 1;
	int correct = 0;
	int incorrect = 0;

	printSections(DatabaseManager::getInstance().getSections());

	cout << "Выберите раздел: ";
	cin >> section;

	vector<Test> tests = DatabaseManager::getInstance().getTestsInSection(section);

	printTests(tests);

	cout << "Выберите тест: ";
	cin >> test_name;

	Test test = getTestByName(tests, test_name);

	for (Test::Question question : test.getQuestions())
	{
		string user_answer;
		int answer_counter = 1;

		cout << "Вопрос N" << counter << ":\n";
		cout << question.getQuestion() << endl;

		cout << "Варианты ответа:\n";
		for (string answer : question.getAnswers())
		{
			cout << "[" << answer_counter << "] " << answer;
			answer_counter++;
		}
		cout << endl;

		cout << "Введите ответ: ";
		cin >> user_answer;

		if (user_answer == question.getRightAnswer())
			correct++;
		else
			incorrect++;
		
		counter++;
	}

	DatabaseManager::getInstance().addUserResult(DatabaseManager::getInstance().getUserIdByLogin(login), TestResult(correct, incorrect));
	
	start(login);
}

void TesterArea::chooseResult(string login)
{
	string section;
	string name;
	vector<string> sections = DatabaseManager::getInstance().getSections();
	vector<Test> tests;

	printSections(sections);

	cout << "Введите название нужного раздела: ";
	cin >> section;

	tests = DatabaseManager::getInstance().getTestsInSection(section);

	printTests(tests);

	cout << "Введите название нужного теста: ";
	cin >> name;

	Test test = getTestByName(tests, name);

	cout << "| Название: " << test.getName() << endl;
	cout << "| Раздел: " << test.getSection() << endl;
	cout << "| Результат:\n";
	printTestResult(DatabaseManager::getInstance().getUserResult(DatabaseManager::getInstance().getUserIdByLogin(login), test.getName()));

	start(login);
}

void TesterArea::printSections(vector<string> sections)
{
	for (string section : sections)
	{
		cout << format("~~~~~~~~* {} *~~~~~~~~\n", section);
	}
}

void TesterArea::printTests(vector<Test> tests)
{
	for (Test test : tests)
	{
		cout << format("--------* {} *--------\n", test.getName());
	}
}

Test TesterArea::getTestByName(vector<Test> tests, string name)
{
	for (Test test : tests)
	{
		if (test.getName() == name)
		{
			return test;
		}
	}
}

void TesterArea::printTestResult(TestResult result)
{
	cout << "  | Правильные ответы: " << result.getCorrect() << endl;
	cout << "  | Неправильные ответы: " << result.getIncorrect() << endl;
	cout << "  | Процент правильных ответов: " << result.getCorrectPerc() << endl;
	cout << "  | Процент неправильных ответов: " << result.getIncorrectPerc() << endl;
	cout << "  | Оценка: " << result.getMark() << endl;
}