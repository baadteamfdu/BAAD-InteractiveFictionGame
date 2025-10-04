#include "Room.h"
#include <iostream>
using namespace std;

//constructor
Room::Room(string id, string name, string description): id(id), name(name), description(description) { //I don't know if using this keyword is better than what I have or not

}

//getters
string Room::getId() {
	return id;
}

string Room::getDescription() {
	return description;
}

string Room::getName() {
	return name;
}