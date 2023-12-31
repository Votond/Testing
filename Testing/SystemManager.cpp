#include "Includes.h"
#include "SystemManager.h"
#include "DatabaseManager.cpp"
#include "User.h"

class SystemManager
{
public:
	void start()
	{
		int action;

		cout << "-------* Тестирование *-------\nВход или регистрация?\n 1 - Вход\n2 - Регистрация\n";
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
		if (DatabaseManager::getInstance().getAccountsQantity() < 1)
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

		if (DatabaseManager::getInstance().checkExistence(login, password))
		{
			
		};
	}

private:
	User dataInput(User::USER_TYPE user_type)
	{
		string fio;
		string address;
		string phone_number;
		string login;
		string password;

		cout << "----* Регистрация администратора *----\nВведите ФИО без пробелов: ";
		cin >> fio;

		cout << "Введите домашний адрес без пробелов: ";
		cin >> address;

		cout << "Введите номер телефона без пробелов: ";
		cin >> phone_number;

		cout << "Придумайте и введите логин без пробелов: ";
		cin >> login;

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