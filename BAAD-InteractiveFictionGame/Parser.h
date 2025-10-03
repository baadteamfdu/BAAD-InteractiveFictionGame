#pragma once
#include <string>
#include "Actions.h"
using namespace std;


class Parser
{
	public:
		bool parse(string input, Actions action, string noun); //boolean to check if the input was valid
};

