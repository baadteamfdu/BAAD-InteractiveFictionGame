#include "Game.h"
#include <iostream>
using namespace std;

void Game::init() {
	Room* cryoStart = new Room("cryo01", "Cryo Chamber", "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent. ");
    setCurrentRoom(cryoStart);
}

Room* Game::getCurrentRoom(){
	return currentRoom;
}

void Game::setCurrentRoom(Room * nextRoom) {
    currentRoom = nextRoom;
}

Parser Game::getParser() {
	return parser;
}

void Game::getHelp() {
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

void Game::process(Actions action, string noun) {
	//placeholder it will need handlers for each enum possiblity (action from Actions) with each noun
    // Add a seperate command not understood. for if the command did nothing So typing something like "look egg" when there is no egg says that it doesn't work	
}