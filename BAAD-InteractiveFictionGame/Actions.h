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
	PRESS,
	WAKE,        // to wake up captain
	SERVE,       // to serve water to captain
	READ,
	TALK
};

Actions stringToAction(string action);
