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
        "On the floor there's a keycard\n"
        "In the corner of the room there's a sealed door with a card-reader on it\n"
    );
    setCurrentRoom(cryoStart);

    // Add objects to starting room
    Object* keycard = new Object("Keycard", "A Level A access card with a magnetic stripe.", true);
    cryoStart->addObject(keycard);
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
                } else {
                    cout << "There's nothing to see.\n";
                }
            }
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            else if (noun == "keycard" || noun == "Keycard") {
                if (!inventory.gotObject("Keycard")) {
                    cout << "You don't have the keycard.\n";
                } else {
                    // requires Inventory::getObject(string) to be implemented
                    const Object* kc = inventory.getObject("Keycard");
                    if (kc) cout << kc->getDescription() << endl;
                    else    cout << "You examine the keycard.\n";
                }
            }
            else {
                cout << "Look at what?\n";
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
