#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include "Alien.h"
#include <string>
using namespace std;

class Game {
private:
    Room* currentRoom = nullptr;
    Parser parser;
    Inventory inventory;
    Alien alien;
    bool foundcode1 = false;             // code in bathroom set to false by default. to check of the player got the first half.
    bool foundcode2 = false;             // code found in book set to false by default.to check of the player got the second half.
    int passcode;                        // random 4 digit passocde.
    int passcode1;                       //variable to store first half of the passcode.
    int passcode2;                       // varuiable to store second half of the passcode.
    vector<Room*> allRooms;             //this vector stores all rooms for the map

public:
    void init();
    void process();
    void getHelp();

    Room* getCurrentRoom();
    void setCurrentRoom(Room* nextRoom);
  

	void useKeycard(Object* door);
	void goDoor(const string& doorName);
    void typeCode(int enteredCode); 

    void displayMap() const; //this code will display the map for the game
};
