#include "Game.h"
#include <iostream>
using namespace std;

void Game::init() {
	Room* cryoStart = new Room("cryo01", "Cryo Chamber", "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent. ");
}

Room* Game::getCurrentRoom(){
	return currentRoom;
}

Parser Game::getParser() {
	return parser;
}