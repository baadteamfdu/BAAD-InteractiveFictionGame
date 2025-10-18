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
	// Create rooms
    Room* cryoStart = new Room(
        "cryo01",
        "Cryo Chamber",
        "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n"
    );
	Room* cryoHall = new Room( 
		"cryoHall",
		"Cryo Hallway",
		"A long hallway with doors on either side. The lights flicker occasionally.\n"
	);
	Room* escapePod = new Room(
		"escapePod",
		"Escape Pod Chamber",
		"A small room with blinking lights and a sealed escape pod.\n"
	);
	Room* workersRoom = new Room(
		"workersRoom",
		"Worker's Room",
		"A small room with bunks and personal lockers for the station's crew.\n"
	);
	Room* bathroom = new Room(
		"bathroom",
		"Bathroom",
		"A small, sterile bathroom with a sink and a mirror.\n"
	);
	Room* finalRoom = new Room(
		"finalRoom",
		"Abandoned Control Room",
		"The control room is dark and silent, with flickering monitors and empty chairs.\n"
	);

    setCurrentRoom(cryoStart);

    // Add objects to starting room

    //NOTE ALL OBJECTS MUST HAVE LOWERCASE NAMES AT LEAST FOR NOW, AS TOLOWER IS IN PARSER
    // Add objects to starting room
    Object* keycard = new Object("keycard", "A Level A access card with a magnetic stripe.", true);
    cryoStart->addObject(keycard);

    // Creating doors
    Object* cryoDoor = new Object("cryo door", "A door with a card reader", false, true);
    Object* escapePodDoor = new Object("escape pod door", "A door to the Escape Pod Chamber", false, false);
    Object* workersDoor = new Object("workers door", "A door to the Worker’s Room", false, false);
    Object* bathroomDoor = new Object("bathroom door", "A door to the Bathroom", false, false);
    Object* finalRoomDoor = new Object("final room door", "A door to the Final Room", false, false);
	
	// Adding doors to rooms
    cryoStart->addObject(cryoDoor);
    cryoHall->addObject(cryoDoor);

    cryoHall->addObject(escapePodDoor);
    escapePod->addObject(escapePodDoor);

    cryoHall->addObject(workersDoor);
    workersRoom->addObject(workersDoor);

    workersRoom->addObject(bathroomDoor);
    bathroom->addObject(bathroomDoor);

    escapePod->addObject(finalRoomDoor);
    finalRoom->addObject(finalRoomDoor);
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
//void Game::goDoor(Object* door) {
//    if (door->getIsLocked() == true) {
//		cout << "The door is locked. You need to unlock it first.\n";
//	}
//    else {
//        cout << "You go through the door to the next room.\n";
//		currentRoom = currentRoom->getNeighbour(); // move to the neighbouring room
//		cout << currentRoom->getDescription() << endl; // describe the new room
//		door->setIsLocked(true); // lock the door again after going through
//    }
//}

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
		
        case Actions::USE:
		    if (noun.empty()) { //check if the user inputted a noun
                cout << "Use what?\n";
                break;
            }
			else if (noun == "keycard") { //check if the user inputted keycard
                if (!inventory.gotObject("keycard")) { //check if the user has the keycard
                    cout << "You don't have a keycard to use.\n";
                    break;
                }
                Object* door = currentRoom->getObject("door"); //check if there is a door in the room
				if (door) {
				    useKeycard(door); //use the function
				}
				else {
					cout << "There is no door here to use the keycard on.\n"; //if there is no door in the room
				}
			}
			else {
				cout << "You can't use that.\n"; //if the user does not have the keycard
			}
            break;

		case Actions::GO:
		case Actions::OPEN:
			if (noun.empty()) { //check if the user inputted a noun
				cout << "Go where?\n";
			}
            else if (noun == "door") {
                Object* door = currentRoom->getObject("door"); //check if there is a door in the room
                if (door) {
                    goDoor(door); //use the function
                }
                else {
                    cout << "There is no door here.\n";
                }
            }
            else{
                cout << "You can't do that right now." << endl;
            }
			break;
        default:
            cout << "You can't do that right now.\n";
            break;
        }
    }
}
