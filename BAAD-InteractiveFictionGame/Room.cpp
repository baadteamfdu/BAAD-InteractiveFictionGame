#include "Room.h"
#include <iostream>
using namespace std;

//constructor
Room::Room(string id, string name, string description) : id(id), name(name), description(description) { //I don't know if using this keyword is better than what I have or not
}

//getters
string Room::getId() {
    return id;
}

string Room::getName() {
    return name;
}
string Room::getDescription() {
    return description;
}

Object* Room::getObject(string name) {
    for (auto* obj : roomObjects) {
        if (obj && obj->getName() == name) {
            return obj;
        }
    }
    return nullptr;
}

void Room::setPosition(int x, int y)
{
    nX = x;
    nY = y;
}
int Room::getX()
{
    return nX;
}
int Room::getY()
{
    return nY;
}


// adds an object to the roomObjects vector 
void Room::addObject(Object* object) {
    roomObjects.push_back(object);
}

// removes the object from the roomObjects vector
void Room::removeObject(string name) 
{
    auto it = remove_if(roomObjects.begin(), roomObjects.end(),
        [&](Object* obj) { return obj && obj->getName() == name; });
    roomObjects.erase(it, roomObjects.end());
}

//couts all objects in the room
void Room::printAllObjects() 
{
    for (Object* obj : roomObjects) 
    {
        cout << obj->getName() << endl;
    }
}
//getter for neighbour
Room* Room::getNeighbour(const string& doorName) { // getter for neighbour
	if (neighbours.find(doorName) != neighbours.end()) { // check if doorName exists in the map
		return neighbours[doorName]; // return the corresponding Room pointer
    }
	return nullptr; // return nullptr if not found
}
//setter for neighboor
void Room::setNeighbour(const string& doorName, Room* room) { // setter for neighbour
	neighbours[doorName] = room; // set the Room pointer for the given doorName
}

void Room::setDescription(string des) {
    description = des;
}