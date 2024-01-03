#include "Includes.h"
#include "SystemManager.h"
#include "DatabaseManager.cpp"
#include "User.h"
#include "AdminArea.cpp"
#include "TesterArea.cpp"

class SystemManager
{
	static SystemManager instance();

public:
	static SystemManager getInstance()
	{
		return instance();
	}

	void start()
	{
		int action;

		cout << "-------* Тестирование *-------\nВход или регистрация?\n1 - Вход\n2 - Регистрация\n";
		cin >> action;

		switch (action)
		{
		case 1:
			login();
			break;

		case 2:
			registration();
			break;

		default:
			cout << "Некорректный ввод\n";
			start();
			break;
		}
	}

	void registration()
	{
		if (DatabaseManager::getInstance().getAccountsQuantity() < 1)
		{
			DatabaseManager::getInstance().addUser(dataInput(User::ADMIN));
		}
		else
		{
			DatabaseManager::getInstance().addUser(dataInput(User::TESTER));
		}

		cout << "Вы зарегистрированы\n";

		login();
	}

	void login()
	{
		string login;
		string password;

		cout << "Введите логин: ";
		cin >> login;

		cout << "Введите пароль: ";
		cin >> password;

		pair<bool, User::USER_TYPE> pair = DatabaseManager::getInstance().validate(login, password);

		if (pair.first)
		{
			switch (pair.second)
			{
			case User::ADMIN:
				// TODO
				break;

			case User::TESTER:
				TesterArea::getInstance().start(login);
				break;
			}
		}
		else
		{
			cout << "Неправильный логин или пароль\n";
			this->login();
		}
	}

private:
	User dataInput(User::USER_TYPE user_type)
	{
		string fio;
		string address;
		string phone_number;
		string login;
		string password;

		cout << "------* Регистрация *------\nВведите ФИО без пробелов: ";
		cin >> fio;

		cout << "Введите домашний адрес без пробелов: ";
		cin >> address;

		cout << "Введите номер телефона без пробелов: ";
		cin >> phone_number;

		cout << "Придумайте и введите логин без пробелов: ";
		cin >> login;

		if (DatabaseManager::getInstance().checkExistence(login))
		{
			cout << "Аккаунт с таким логином уже существует. Выберите другой логин\n";
			dataInput(user_type);
		}

		cout << "Придумайте и введите пароль без пробелов: ";
		cin >> password;

		switch (user_type)
		{
		case User::ADMIN:
			return User{fio, address, phone_number, login, password, User::ADMIN};

		case User::TESTER:
			return User{ fio, address, phone_number, login, password, User::TESTER };
		}
	}
};