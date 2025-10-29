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
	MAP,
	TYPE,           //for typing passcode
	INVALID,
	HIDE,
	UNHIDE
};

Actions stringToAction(string action);
