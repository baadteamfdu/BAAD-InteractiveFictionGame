#include "Object.h"
#include <iostream>
using namespace std;

//use inheritance for object types like takeable maybe and maybe exits/door and the base class could have things like id name and description etc

Object::Object(string name, string description, bool takeable) :name(name), description(description), takeable(takeable) {}
Object::Object(string name, string description, bool takeable, bool isLocked) :name(name), description(description), takeable(takeable), isLocked(isLocked) {}

string Object::getName() { return name; }
string Object::getDescription() { return description; }
bool Object::isTakeable() { return takeable; }
bool Object::getIsLocked() { return isLocked; }