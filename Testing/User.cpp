#include "Includes.h"
#include "User.h"

class User
{
public:
	static enum USER_TYPE
	{
		TESTER,
		ADMIN
	};

private:
	string fio;
	string address;
	string phone_number;
	string login;
	string password;
	USER_TYPE user_type;

public:
	User(const string& fio, const string& address, const string& phone_number, const string& login, const string& password, const USER_TYPE& user_type)
		: fio(fio), address(address), phone_number(phone_number), login(login), password(password), user_type(user_type)
	{
		
	}

	User(const string& fio, const string& address, const string& phone_number, const USER_TYPE& user_type)
		: fio(fio), address(address), phone_number(phone_number), user_type(user_type)
	{

	}

	string getFio() { return fio; }
	string getAddress() { return address; }
	string getPhoneNumber() { return phone_number; }
	string getLogin() { return login; }
	string getPassword() { return password; }
	USER_TYPE getUserType() { return user_type; }
};