#include "Includes.h"
#include "TesterArea.h"

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
		
	}

	void startTest(int id)
	{
		
	}

	void viewResult(int id)
	{
		
	}
};