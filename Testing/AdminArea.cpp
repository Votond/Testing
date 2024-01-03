#include "Includes.h"
#include "AdminArea.h"

class AdminArea
{
	static AdminArea instance();

public:
	static AdminArea getInstance()
	{
		return instance();
	}
};