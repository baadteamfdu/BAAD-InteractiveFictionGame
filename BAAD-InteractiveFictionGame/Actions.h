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
	INVENTORY,
	INVALID
};

Actions stringToAction(std::string action);
