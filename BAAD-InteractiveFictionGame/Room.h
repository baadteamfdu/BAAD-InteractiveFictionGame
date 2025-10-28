#pragma once
#include <vector>
#include <string>
#include <map>
#include "Object.h"
using namespace std;

class Room
{
private:

	string id;
	string name;
	string description;
	vector<Object*> roomObjects;
	map<string, Room*> neighbours; // map of direction to neighbouring Room pointers

	int nX = 0;
	int nY = 0;
public:

	Room(string id, string name, string description);
	string getId();
	string getName();
	string getDescription();

	Object* getObject(string name); //gets the object but returns nullptr if the object couldn't be found
	void addObject(Object* object); //adds an object to the roomObjects vector 
	void removeObject(string name); //removes the object from the roomObjects vector   
	void printAllObjects(); // displays all objects in the room
	void setNeighbour(const string& doorName, Room* room); // setter for neighbour
	Room* getNeighbour(const string& doorName); // getter for neighbour

	//this code sets the positions for where the rooms are and the player
	void setPosition(int x, int y)
	{
		nX = x;
		nY = y;
	}
	int getX()
	{
		return nX;
	}
	int getY()
	{
		return nY;
	}
};


