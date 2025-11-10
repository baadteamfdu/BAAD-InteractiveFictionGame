#include "Inventory.h"
#include <iostream>
using namespace std;

void Inventory::addObject(Object* object) {
	objects.push_back(object);                     // adds an object in the inventory. by default pushes it back.

}

void Inventory::showInventory() {
	if (objects.empty()) {
		cout << "Your inventory is empty" << endl;        // Showinventory function... If Empty
		return;
	}

	cout << "Objects in your inventory: (use look <object> for description)" << endl;
	for (int i = 0; i < objects.size(); i++) {

		cout << objects[i]->getName() << endl; // if there are an object. prints the name.
	}
}

bool Inventory::gotObject(string objectName) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getName() == objectName) {                        //Bool function to check if the inventory has the object player types (e.g. Keycard)
			return true;
		}
	}
	return false;

}
Object* Inventory::getObject(string objectName) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getName() == objectName) {
			return  objects[i]; // return pointer to the stored object
		}
	}
	return nullptr;
}

bool Inventory::deleteObject(Object* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {   // found the matching pointer
			delete objects[i];        // free memory (only if created with new)
			objects.erase(objects.begin() + i);  // remove from vector
			return true;
		}
	}
	return false;  // not found
}