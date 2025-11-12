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
	PEEK,
	TYPE,           //for typing passcode
	INVALID,
	HIDE,
	UNHIDE,
	RUN,
	PRESS
};

Actions stringToAction(string action);
