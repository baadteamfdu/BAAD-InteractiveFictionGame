#pragma once

#include <string>
#include "Object.h"
using namespace std;


class Room
{
public:
	Room(string id, string name, string description);
	string getDescription();
	string getName();
	string getId();
private: 
	string id;
	string name;
	string description;
};

