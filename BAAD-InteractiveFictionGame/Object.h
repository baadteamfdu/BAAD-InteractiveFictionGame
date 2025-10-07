#pragma once
#include "Actions.h"
#include <string>
using namespace std;

class Object
{
public:
	string name;
	string description;
	bool take;
	Object(string n, string d, bool t) {name = n; description = d; take = t;}
};

