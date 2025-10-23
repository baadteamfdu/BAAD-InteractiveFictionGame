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
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer == true) {
		idleCounter++;
		if (idleCounter > killThreshold) {
			killPlayer();
			}
	}
	if (turnCounter > moveThreshold && isActive == true) {
		move(playerCurrentRoom);
	}
}
void Alien::move(Room* playerCurrentRoom) {
	if (alienCurrentRoom == nullptr) {
		alienCurrentRoom = roomList[1]; //should always be cryohall
		sawPlayer = true;
		return;
	}
	if (alienCurrentRoom == playerCurrentRoom) {
		sawPlayer = true;
	}
	leave();
}

void Alien:: killPlayer() {
	cout << "You were caught by the alien" << endl;
	cout << "Game Over" << endl;
	exit(0);
}

void Alien::leave() {
	sawPlayer = false;
	idleCounter = 0;
	turnCounter = 0;
	moveThreshold = (rand() % 5 + 1);
	killThreshold = rand() % 3 + 1;
	Room* moveRoom = alienCurrentRoom;
	while (moveRoom == alienCurrentRoom) {
		moveRoom = roomList[(rand() % roomList.size())];
	}
	alienCurrentRoom = moveRoom;
}
 
void Alien::addRoom(Room* newRoom) {
	roomList.push_back(newRoom);
}