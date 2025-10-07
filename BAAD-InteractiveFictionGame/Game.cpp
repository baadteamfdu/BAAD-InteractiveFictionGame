#include "Game.h"
#include <iostream>
using namespace std;

void Game::init() { //sets current room to the starting room and initalizes the starting room to exist
    Room* cryoStart = new Room
    ("cryo01", "Cryo Chamber", "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n "
        "On the floor there's a keycard\n"
        "In the corner of the room there's a sealed door with a card-reader on it\n;"
    );
    setCurrentRoom(cryoStart);
    //will need expansion to include objects in room and all other rooms, all exits and connecting all rooms, etc

}

//getters for current room and parser and setter for current room 
Room* Game::getCurrentRoom(){
	return currentRoom;
}

void Game::setCurrentRoom(Room * nextRoom) {
    currentRoom = nextRoom;
}

void Game::getHelp() { //prints out available commands
    cout << "Available commands:" << endl;
    cout << "go <direction>: move between rooms" << endl;
    cout << "take <item>" << endl;
    cout << "use <item>" << endl;
    cout << "open <object>" << endl;
    cout << "look <item>" << endl;
    cout << "look around / look room" << endl;
    cout << "inventory / look inventory" << endl; //maybe also check inventory at some point
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
                else {
                    cout << "Look at what?\n";
                }
                break;
            }
        }

	//placeholder it will need handlers for each enum possiblity (action from Actions) with each noun
    // Add a seperate command not understood. for if the command did nothing So typing something like "look egg" when there is no egg says that it doesn't work	
}