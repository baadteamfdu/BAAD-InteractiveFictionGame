#include <iostream>
#include "Alien.h"

using namespace std;


Alien::Alien() {
	moveThreshold = rand() % 5 + 2;
	cout << moveThreshold << endl;
	killThreshold = rand() % 3 + 1;
	cout << killThreshold << endl;
}

void Alien::setActive(bool active) {
	isActive = active;
}

bool Alien::getIsActive() {
	return isActive;
}
void Alien::setSawPlayer(bool seen) {
	sawPlayer = seen;
}
bool Alien::getSawPlayer() {
	return sawPlayer;
}

void Alien:: increaseTurnCounter(Room * playerCurrentRoom) {
	turnCounter++;
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer != true) {
		sawPlayer = true;
		cout << "The alien notices you... run!" << endl;
	}
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer == true) {	
		idleCounter++;
		if (idleCounter > killThreshold) {
			killPlayer();
			}
	}
	if (turnCounter > moveThreshold && isActive == true && sawPlayer == false) {
		move();
	}
}
void Alien::move() {
	if (alienCurrentRoom == nullptr) {
		alienCurrentRoom = roomList[1]; //should always be cryohall
		return; //so they don't leave early
	}
	leave();
}

void Alien:: killPlayer() {
	cout << "You were caught by the alien" << endl;
	cout << "Game Over" << endl;
	exit(0);
}

void Alien::leave() {
	Room* moveRoom = alienCurrentRoom;
	while (moveRoom == alienCurrentRoom) {
		moveRoom = roomList[(rand() % roomList.size())];
	}
	sawPlayer = false;
	idleCounter = 0;
	turnCounter = 0;
	moveThreshold = (rand() % 5 + 1);
	killThreshold = rand() % 3 + 1;
	alienCurrentRoom = moveRoom;
}
 
void Alien::addRoom(Room* newRoom) {
	roomList.push_back(newRoom);
}