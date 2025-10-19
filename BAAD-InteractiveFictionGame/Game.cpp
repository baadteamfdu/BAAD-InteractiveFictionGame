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

void Game::init() { 
    
    // sets current room to the starting room and initializes the starting room to exist
	// Create rooms

    srand(time(0));  // initialize random seed.
    passcode = rand() % 9000 + 1000; // since there could only be 9000 odds for a four digit passcode and it would start from 1000.
    passcode1 = passcode / 100;      // stores the first two digits for passcode1
    passcode2 = passcode % 100;      // stores the last two digits for passcode 2


    // assigning the booleans false by default. obviously passcode would not be found at the begining.
    foundcode1 = false;              
    foundcode2 = false;

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
		"A small room with blinking lights and a sealed escape pod. The others appear broken. \n"
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

    // Book in worker's room
    Object* book = new Object("book", "An old logbook", true); // creating a book object
    workersRoom->addObject(book); //placing that book in the workers woom. Offcourse is takeable

    // stall in bathroom

    Object* stall = new Object("stall", "Looks like it has been dead for a while It might open", false, true);  // creating a stall object.
    stall->setIsOpen(false);
    bathroom->addObject(stall); // Placing in the bathroom.

    //code halves inside objects 
  //  Object* codePart1 = new Object("code part 1", "Half of the passcode: '--" + to_string(passcode % 100) + "'", true);
  //  Object* codePart2 = new Object("code part 2", "Half of the passcode: '" + to_string(passcode / 100) + "--'", true);
  //  stall->addContainedObject(codePart1);
  //  book->addContainedObject(codePart2);




    // Creating doors
    Object* cryoDoor = new Object("cryo door", "A door with a card reader", false, true);
    Object* escapePodDoor = new Object("chamber door", "A door to the Escape Pod Chamber", false, true);
    Object* workersDoor = new Object("worker door", "A door to the Worker’s Room", false, true);
    Object* bathroomDoor = new Object("bathroom door", "A door to the Bathroom", false, false);
    Object* finalRoomDoor = new Object("pod door", "A door to the Final Room", false, true);
	
    // passcode door
    Object* passcodeDoor = new Object("passcode door", "A door with a keypad lock", false, true); // added the passcode door object.
    passcodeDoor->setIsPasscodeLocked(true); // door is locked
    passcodeDoor->setPasscode(passcode);  
   
	// Adding doors to rooms

  

    cryoStart->addObject(cryoDoor);
    cryoHall->addObject(cryoDoor);

    cryoHall->addObject(passcodeDoor);    //adding the passcode door
    escapePod->addObject(passcodeDoor);

    cryoHall->addObject(workersDoor);
    workersRoom->addObject(workersDoor);

    workersRoom->addObject(bathroomDoor);
    bathroom->addObject(bathroomDoor);

    escapePod->addObject(finalRoomDoor);
    finalRoom->addObject(finalRoomDoor);

    //Connect rooms
    cryoStart->setNeighbour("cryo door", cryoHall);
    cryoHall->setNeighbour("cryo door", cryoStart);

    cryoHall->setNeighbour("passcode door", escapePod);
    escapePod->setNeighbour("passcode door", cryoHall);

    cryoHall->setNeighbour("worker door", workersRoom);
    workersRoom->setNeighbour("worker door", cryoHall);

    workersRoom->setNeighbour("bathroom door", bathroom);
    bathroom->setNeighbour("bathroom door", workersRoom);

    escapePod->setNeighbour("pod door", finalRoom);
    finalRoom->setNeighbour("pod door", escapePod);
}

Room* Game::getCurrentRoom() {
    return currentRoom;
}

void Game::setCurrentRoom(Room* nextRoom) {
    currentRoom = nextRoom;
}

void Game::getHelp() { // prints out available commands
    cout << "Available commands:\n";
    cout << "go <door name>       : move between rooms\n";
    cout << "take <item>\n";
    cout << "use <item> <door name> \n";
    cout << "open <door name> (or <object name>) \n";
    cout << "look <item>\n";
    cout << "look around / look room\n";
    cout << "inventory / look inventory\n";
    cout << "help\n";
}

// New method to use a keycard on a door
void Game::useKeycard(Object* door) {
    if (!door) {
        cout << "There's no such door here.\n";
        return;
    }

    if (door->getIsLocked()) {
        door->setIsLocked(false); // unlock the door
        cout << "You swipe the keycard, and the door unlocks with a loud beep.\n";
      
    }
    else {
        cout << "The door is already unlocked.\n";
    }
}


// New method to check if the current room has the passcodedoor.

void Game::typeCode(int enteredCode)
{
    // check current room for passcode door
    Object* door = currentRoom->getObject("passcode door");
    if (!door)
    {
        cout << "There is no keypad door here.\n";
        return;
    }
    if (!foundcode1 ||!foundcode2) {
        cout << "You don't have both halves of the passcode yet.\n";
        return;
    }

    if (enteredCode == passcode) {
        cout << "The keypad flashes green. The door unlocks.\n";
        door->setIsLocked(false);
    }
    else { cout << "Incorrect code. Try again.\n"; }
}


void Game::goDoor(const string& doorName) { // New method to go through a door
	Object* door = currentRoom->getObject(doorName); //check if the door exists in the current room
	if (!door) {
		cout << "There is no " << doorName << " here.\n";
		return;
	}
    if (door->isTakeable()) { //stop player trying to open or go a keycard
        cout << "You cannot open this or go through it. \n";
        return;
    }

    // check for passcode locked door
    if (door->getIsPasscodeLocked()) {
        if (door->getIsLocked()) {
            std::cout << "The door is locked. You must enter the passcode.\n";
            return;
        }
    }
    // check for usual keycard doors
    if (door->getIsLocked()) {
        cout << "The door is locked.\n";
        return;
    }

     Room* nextRoom = currentRoom->getNeighbour(doorName); // get the neighbouring room through the door
     if (nextRoom) {
         cout << "You go through the " << doorName << " and enter the next room.\n";
         setCurrentRoom(nextRoom); // move to the neighbouring room
         cout << currentRoom->getDescription() << endl;
         door->setIsLocked(true); // lock the door again after going through
         if ((door->getName()) == "bathroom door") { //don't lock player in bathroom 
                door->setIsLocked(false);
            
         }
                 
     }
     else {
         cout << "There is no room connected to this door.\n";
     }
     
    
	
}

void Game::process()
{
    string input, noun, whatToUseOn;
    Actions action;

    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, input)) break; // handle EOF cleanly

        if (!parser.parse(input, action, noun, whatToUseOn)) {
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
  
                }
                if (currentRoom->getName() == "bathroom") {
                    Object* stall = currentRoom->getObject("stall");
                    if (stall && stall->getIsOpen()) {
                        cout << "Inside the stall, you notice something scratched into the wall: '--"
                            << passcode2 << "'\n";
                    }
                }
            }
            else if (noun == "stall") {
                Object* stall = currentRoom->getObject("stall");
                if (stall) {
                    if (stall->getIsOpen()) {
                        cout << "Inside the stall, you see part of a passcode: '--"
                            << passcode2 << "'\n";
                    }
                    else {
                        cout << "It's a closed stall.\n";
                    }
                }
                else {
                    cout << "There's no stall here.\n";
                }
            }
            else if (noun == "book") {
                if (inventory.gotObject("book")) {
                    foundcode2 = true;
                    cout << "You flip through the book and find half a passcode: '" << passcode1 << "--'.\n";
                    foundcode2 = true;
                }
                else {
                    cout << "There's nothing to see.\n";
                }
            }
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            else if (noun.empty()) {
                cout << "Look at what?\n";
            }
            else {
                Object* obj = currentRoom->getObject(noun);
                if (obj) {
                    cout << obj->getDescription() << endl;
                }
                else if (inventory.gotObject(noun)) {
                    Object* invobj = inventory.getObject(noun);
                    if (invobj) cout << invobj->getDescription() << endl;
                    else cout << "You examine the keycard.\n";
                }
                else {
                    cout << "You don't have the " << noun << ".\n";
                }
            }
            break;

        case Actions::TAKE:
            if (noun.empty()) {
                cout << "Take what?\n";
                break;
            }

            if (!currentRoom) {
                cout << "There's nowhere to take that from.\n";
                break;
            }

            {
                Object* obj = currentRoom->getObject(noun);
                if (!obj) {
                    cout << "There is no " << noun << " here.\n";
                    break;
                }

                if (!obj->isTakeable()) {
                    cout << "You cannot take this object.\n";
                    break;
                }

                inventory.addObject(obj);
                currentRoom->removeObject(noun);
                cout << "You picked up the " << noun << ".\n";
            }
            break;

        case Actions::INVENTORY:
            inventory.showInventory();
            break;

        case Actions::USE:
            if (noun.empty()) {
                cout << "Use what?\n";
                break;
            }

            if (noun == "keycard") {
                if (!inventory.gotObject("keycard")) {
                    cout << "You don't have a keycard to use.\n";
                    break;
                }

                if (whatToUseOn.empty()) {
                    cout << "Use on what?\n";
                    break;
                }

                Object* door = currentRoom->getObject(whatToUseOn);
                if (door) {
                    useKeycard(door);
                }
                else {
                    cout << "There is no door by that name here to use the keycard on.\n";
                }
            }
            else {
                cout << "You can't use that.\n";
            }
            break;

        case Actions::GO:
        case Actions::OPEN:
            if (noun.empty()) {
                cout << "Where?\n";
                break;
            }

            if (noun == "stall") {
                Object* obj = currentRoom->getObject("stall");
                if (obj) {
                    if (!obj->getIsOpen()) {
                        obj->setIsOpen(true);
                        foundcode1 = true;
                        cout << "You open the stall.\n";
                    }
                    else cout << "Thestall is already open.\n";
                }
                else {
                    cout << "There's no stall here.\n";
                }
            }
            else {
                goDoor(noun);
            }
            break;

        case Actions::TYPE:
            if (noun.empty()) {
                cout << "Enter a code.\n";
                break;
            }
            try {
                int entered = std::stoi(noun);
                typeCode(entered);
            }
            catch (...) {
                cout << "Invalid code format.\n";
            }
            break;

        default:
            cout << "You can't do that right now.\n";
            break;
        } 
    } 
} 
