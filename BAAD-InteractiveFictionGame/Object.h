#pragma once
#include "Actions.h"
#include <string>
using namespace std;

class Object
{

	/* Change From Sami....
	keeping the member variable private so that other classes or function are not able to access it.
	But would have to make the constructor public so that the compiler compiles it successfully. (encapsulation)*
	Additionally, setting the keycard to false because its not a regular item and will not be used everytime..saves typing...
	*/

private:
	string name;
	string description;
	bool takeable;
public:

	// getters

	Object(string n, string d, bool  takeable);
	string getName();
	string getDescription();
	bool isTakeable();

};