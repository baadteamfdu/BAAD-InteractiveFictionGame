#include "Object.h"
#include <iostream>
using namespace std;

//use inheritance for object types like takeable maybe and maybe exits/door and the base class could have things like id name and description etc

Object::Object(string name, string description, bool takeable)
    : name(name), description(description), takeable(takeable),
    isLocked(false), isPasscodeLocked(false), passcode(0), isOpen(false), isSafeZone(false){
}


Object::Object(string name, string description, bool takeable, bool isLocked)
    : name(name), description(description), takeable(takeable),
    isLocked(isLocked), isPasscodeLocked(false), passcode(0), isOpen(false), isSafeZone(false) {
}

Object::Object(string name, string description, bool takeable, bool isLocked, bool isSafe) //new constructor for safe zone objects
    : name(name), description(description), takeable(takeable),
    isLocked(isLocked), isPasscodeLocked(false), passcode(0), isOpen(false), isSafeZone(isSafe) {
}

//getters	
string Object::getName() { return name; }
string Object::getDescription() { return description; }
bool Object::isTakeable() { return takeable; }
bool Object::getIsLocked() { return isLocked; }
bool Object::getIsPasscodeLocked() { return isPasscodeLocked; }
int Object::getPasscode() { return passcode; }
bool Object::getIsOpen() { return isOpen; }
bool Object::getIsSafeZone() { return isSafeZone; } // returns if the object is a safe zone

//setters
void Object::setIsLocked(bool lock) { isLocked = lock; }
void Object::setIsPasscodeLocked(bool lock) { isPasscodeLocked = lock; }
void Object::setPasscode(int code) { passcode = code; }
void Object::setIsOpen(bool open) { isOpen = open; }
void Object::setIsSafeZone(bool safe) { isSafeZone = safe; } // setter for safe zone
