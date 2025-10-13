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

Object* getObject(string name); //gets the object but returns nullptr if the object couldn't be found
void addObject(Object* object); //adds an object to the roomObjects vector 
void removeObject(string name); //removes the object from the roomObjects vector
vector<Object*> roomObjects;     

