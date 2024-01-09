#pragma once

#include "Includes.h"
#include "UserTest.h"

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
	vector<UserTest> tests;

public:
	User(const string& fio, const string& address, const string& phone_number, const string& login, const string& password, const USER_TYPE& user_type);

	string getFio() { return fio; }
	string getAddress() { return address; }
	string getPhoneNumber() { return phone_number; }
	string getLogin() { return login; }
	string getPassword() { return password; }
	USER_TYPE getUserType() { return user_type; }
	vector<UserTest> getTests() { return tests; }
	void addTest(UserTest test) { tests.push_back(test); }
};
