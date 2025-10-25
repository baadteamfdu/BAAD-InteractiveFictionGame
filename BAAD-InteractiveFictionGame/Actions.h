#pragma once
#include <string>
using namespace std;

enum Actions
{
	LOOK,
	TAKE,
	USE,
	OPEN,
	GO,
	HELP,
	MAP,
	INVENTORY,
	TYPE,           //for typing passcode
	INVALID,
	HIDE,
	UHIDE
};

Actions stringToAction(string action);
