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
	INVALID //used to avoid uninitalized local var
	//add more as needed
};

Actions stringToAction(string action);
