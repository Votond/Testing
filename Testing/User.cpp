#include "User.h"


User::User(const string& fio, const string& address, const string& phone_number, const string& login, const string& password, const USER_TYPE& user_type)
	: fio(fio), address(address), phone_number(phone_number), login(login), password(password), user_type(user_type)
{
	
}