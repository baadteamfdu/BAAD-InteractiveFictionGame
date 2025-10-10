#pragma once
#include "Object.h"
#include <string>
#include <vector>
using namespace std;


class Inventory
{

public:
	void addObject(Object object);  // adds an item to the inventory.
	void showInventory();           // suppose to display all the items in the inventory.
	bool gotObject(string objectName); // checks if the person has the items. 
private:
	vector<Object>objects; // a vector list got created all the objects will get stored here.
	
};

