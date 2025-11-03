#pragma once
#include "Actions.h"
#include <string>
#include <vector>
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
	bool isLocked;								 //new flag to check if door is locked or unlocked.
	bool isPasscodeLocked;						 //new flag for doors that can be unlocked by a passcode. 
	int passcode;                                //variable to store randomly generated 4 digit passcode.
	vector<Object*> containedObjects; // objects inside this object
	bool isOpen;                      // for containers like stall, book, etc.
	bool isSafeZone;                  // for objects that are safe zones
public:

	Object(string n, string d, bool  takeable);
	Object(string n, string d, bool takeable, bool isLocked); //additional constructor for doors and maybe for other locked objects in the future
	Object(string n, string d, bool takeable, bool isLocked, bool isSafe); //additional constructor for safe zone objects
	string getName();
	string getDescription();
	bool isTakeable();

	// getters
	
	bool getIsLocked();
	bool getIsPasscodeLocked();
	int getPasscode();
	bool getIsOpen();
	const vector<Object*>& getContainedObjects(); // stores objects inside another object, maybe a book containg a passcode.
	bool getIsSafeZone(); // to check if the object is a safe zone.

	//setters
	
	void setIsLocked(bool lock);
	void setIsPasscodeLocked(bool lock);
	void setPasscode(int code);
	void setIsOpen(bool open);

	void addContainedObject(Object* obj);
	Object* getContainedObject(string name);

	void setIsSafeZone(bool safe); // setter for safe zone. After implementing new constructor I do not know if this is needed, however leaving it here for now.
};