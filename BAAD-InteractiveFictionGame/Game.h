#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include <string>
using namespace std;

class Game {
private:
    Room* currentRoom = nullptr;
    Parser parser;
    Inventory inventory;
    bool foundcode1 = false;             // code in bathroom set to false by default.
    bool foundcode2 = false;             // code found in book set to false by default.
    int passcode;                        // random 4 digit passcode

public:
    void init();
    void process();
    void getHelp();

    Room* getCurrentRoom();
    void setCurrentRoom(Room* nextRoom);

	void useKeycard(Object* door);
	void goDoor(const string& doorName);
    void typeCode(int enteredCode); 
};
