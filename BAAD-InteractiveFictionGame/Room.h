#pragma once
#include <vector>
#include <string>
#include "Object.h"
using namespace std;

class Room
{
private:

	string id;
	string name;
	string description;

public:

	Room(string id, string name, string description);
	string getId();
	string getName();
	string getDescription();
};

