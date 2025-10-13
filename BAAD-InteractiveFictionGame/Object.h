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
	//public variables to change the state of the object
	bool isLocked; //new flag to check if door is locked or unlocked
	// getters

	Object(string n, string d, bool  takeable);
	Object(string n, string d, bool takeable, bool isLocked); //additional constructor for doors and maybe for other locked objects in the future
	string getName();
	string getDescription();
	bool isTakeable();
	bool getIsLocked();

};