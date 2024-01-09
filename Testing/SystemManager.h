#pragma once
#include "Includes.h"
#include "SystemManager.h"
#include "DatabaseManager.h"
#include "User.h"
#include "AdminArea.h"
#include "TesterArea.h"

class SystemManager
{
	static SystemManager instance();
public:
	static SystemManager getInstance();
	void start();
	void registration();
	void login();
private:
	User dataInput(User::USER_TYPE user_type);
};