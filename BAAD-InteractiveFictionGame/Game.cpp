#include "Game.h"
#include "Room.h"
#include "Object.h"
#include "Inventory.h"
#include "Parser.h"   // make sure this exists; otherwise comment this and use the fallback enum below
#include <iostream>
using namespace std;

// If your Actions enum lives elsewhere, include it there.
// If not, uncomment this fallback:
// enum class Actions { HELP, LOOK, TAKE, INVENTORY };

void Game::init() { // sets current room to the starting room and initializes the starting room to exist
    Room* cryoStart = new Room(
        "cryo01",
        "Cryo Chamber",
        "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n"
    );
	Room* cryoHall = new Room( //new room to work on moving between rooms
		"cryoHall",
		"Cryo Hallway",
		"A long hallway with doors on either side. The lights flicker occasionally.\n"
	);
    setCurrentRoom(cryoStart);

    //NOTE ALL OBJECTS MUST HAVE LOWERCASE NAMES AT LEAST FOR NOW, AS TOLOWER IS IN PARSER
    // Add objects to starting room
    Object* keycard = new Object("keycard", "A Level A access card with a magnetic stripe.", true);
	Object* cryoDoor = new Object("door", "A door with a card reader", false, true); //change to true to make it locked
    cryoStart->addObject(keycard);
    cryoStart->addObject(cryoDoor);
	cryoHall->addObject(cryoDoor); // add the same door object to the other room
	cryoStart->setNeighboor(cryoHall); // set the neighboor of the starting room to the new room
	cryoHall->setNeighboor(cryoStart); // set the neighboor of the new room to the starting room
}

Room* Game::getCurrentRoom() {
    return currentRoom;
}

void Game::setCurrentRoom(Room* nextRoom) {
    currentRoom = nextRoom;
}

void Game::getHelp() { // prints out available commands
    cout << "Available commands:\n";
    cout << "go <direction>       : move between rooms\n";
    cout << "take <item>\n";
    cout << "use <item>\n";
    cout << "open <object>\n";
    cout << "look <item>\n";
    cout << "look around / look room\n";
    cout << "inventory / look inventory\n";
    cout << "help\n";
}

// New method to use a keycard on a door
void Game::useKeycard(Object* door) {
    if (door->getIsLocked() == false) {
		cout << "The door is already unlocked.\n";
    }
    else {
        door->setIsLocked(false); // unlock the door
        cout << "You swipe the keycard, and the door unlocks with a loud beep.\n";
    }
}

// New method to go through a door
void Game::goDoor(Object* door) {
    if (door->getIsLocked() == true) {
		cout << "The door is locked. You need to unlock it first.\n";
	}
    else {
        cout << "You go through the door to the next room.\n";
		currentRoom = currentRoom->getNeighboor(); // move to the neighboring room
		cout << currentRoom->getDescription() << endl; // describe the new room
    }
}

void Game::process() 
{
    string input, noun;
    Actions action;

    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, input)) break; // handle EOF cleanly

        if (!parser.parse(input, action, noun)) {
            cout << "Invalid command. Type 'help' for a list of commands.\n";
            continue;
        }

        switch (action) {
        case Actions::HELP:
            getHelp();
            break;

        case Actions::LOOK:
            if (noun == "around" || noun == "room") {
                if (currentRoom) {
                    cout << currentRoom->getDescription() << endl;
                    cout << "Objects in room:" << endl;
                    currentRoom->printAllObjects();
                    cout << endl;
                } else {
                    cout << "There's nothing to see.\n";
                }
            }
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            else if (noun.empty()) {
                cout << "Look at what? \n";
            }
            else if(inventory.gotObject(noun)) {
                // requires Inventory::getObject(string) to be implemented
                Object* obj = inventory.getObject(noun);
                if (obj) cout << obj->getDescription() << endl;
                else cout << "You examine the keycard.\n";
            } 
            else if (!inventory.gotObject(noun)) {
                cout << "You don't have the " << noun << ".\n";
            }
            break;

        case Actions::TAKE: {
            if (noun.empty()) {
                cout << "Take what?\n";
                break;
            }
            if (!currentRoom) {
                cout << "There's nowhere to take that from.\n";
                break;
            }

            // requires Room::getObject(string), removeObject(string)
            Object* obj = currentRoom->getObject(noun);
            if (!obj) {
                cout << "There is no " << noun << " here.\n";
                break;
            }
            if (!obj->isTakeable()) {
                cout << "You cannot take this object" << endl;
                break;
            }
            // copy into inventory (requires Inventory::addObject(const Object&))
            inventory.addObject(*obj);

            // remove from room and free memory (room owns the pointer)
            currentRoom->removeObject(noun);
            delete obj;

            cout << "You picked up the " << noun << ".\n";
            break;
        }

        case Actions::INVENTORY:
            inventory.showInventory();
            break;

        default:
            cout << "You can't do that right now.\n";
            break;
        }
    }
}
