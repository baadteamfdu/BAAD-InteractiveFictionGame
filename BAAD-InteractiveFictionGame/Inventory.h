#pragma once
#include "Object.h"
#include <string>
#include <vector>
using namespace std;

/*

Change From Sami. will be using a pointer for this project because 
objects often have state that changes during play (e.g. doors, keycards, stall).
and if changes are made on the object it wont reflect on the copies. 
Thats why i felt like working with pointers is a good idea.



*/

class Inventory

{

public:
	void addObject(Object* object);  
	void showInventory();           // suppose to display all the items in the inventory.
	bool gotObject(string objectName); // checks if the person has the items. 

	Object* getObject(string objectName);

private:
	vector<Object*>objects; // a vector list got created all the objects will get stored here. Change for the same reason.

};