#include "Game.h"
#include <iostream>
using namespace std;

void Game::init() { // sets current room to the starting room and initializes the starting room to exist
    Room* cryoStart = new Room
    (
        "cryo01",
        "Cryo Chamber",
        "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n"
        "On the floor there's a keycard\n"
        "In the corner of the room there's a sealed door with a card-reader on it\n"
    );
    setCurrentRoom(cryoStart);

    // --- ADD OBJECTS TO ROOM ---
    // Object* keycard = new Object() // fix constructor:
    Object* keycard = new Object("Keycard", "A Level A access card with a magnetic stripe.", true);
    cryoStart->addObject(keycard);

    // Inventory is a member (Inventory inventory), so nothing else needed to "create" it.
    // (If you had dynamic allocation, you'd do it here; but not necessary.)
}

// getters for current room and parser and setter for current room 
Room* Game::getCurrentRoom() {
    return currentRoom;
}

void Game::setCurrentRoom(Room* nextRoom) {
    currentRoom = nextRoom;
}

void Game::getHelp() { // prints out available commands
    cout << "Available commands:" << endl;
    cout << "go <direction>: move between rooms" << endl;
    cout << "take <item>" << endl;
    cout << "use <item>" << endl;
    cout << "open <object>" << endl;
    cout << "look <item>" << endl;
    cout << "look around / look room" << endl;
    cout << "inventory / look inventory" << endl; // maybe also check inventory at some point
    cout << "help" << endl;
}

void Game::process() 
{
    string input, noun;
    Actions action;

    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "> ";
        getline(cin, input);

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
                cout << currentRoom->getDescription() << endl;
            }
            // add another if else to LOOK case in process where noun == inventory that also runs show inventory
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            // add another if else to LOOK where noun == keycard that gets keycard from inventory
            // and then gets the description and prints it
            else if (noun == "keycard" || noun == "Keycard") {
                if (!inventory.gotObject("Keycard")) {
                    cout << "You don't have the keycard." << endl;
                } else {
                    const Object* kc = inventory.getObject("Keycard");
                    if (kc) cout << kc->getDescription() << endl;
                    else    cout << "You examine the keycard." << endl;
                }
            }
            else {
                cout << "Look at what?\n";
            }
            break;

        case Actions::TAKE:
        {
            // getObject  // add to inventory // removeObject from room
            if (noun.empty()) {
                cout << "Take what?" << endl;
                break;
            }
            if (!currentRoom) {
                cout << "There's nowhere to take that from." << endl;
                break;
            }

            Object* obj = currentRoom->getObject(noun);
            if (!obj) {
                cout << "There is no " << noun << " here." << endl;
                break;
            }

            // Add by value into inventory (simple approach)
            inventory.addObject(*obj);

            // Remove from room, then free memory (room stored a new'ed pointer)
            currentRoom->removeObject(noun);
            delete obj;

            cout << "You picked up the " << noun << "." << endl;
            break;
        }

        case Actions::INVENTORY:
            // showInventory
            inventory.showInventory();
            break;

        default:
            cout << "You can't do that right now." << endl;
            break;
        }
    }

    // placeholder it will need handlers for each enum possibility (action from Actions) with each noun
    // Add a separate 'command not understood' for if the command did nothing (parser covers most of it).
}
