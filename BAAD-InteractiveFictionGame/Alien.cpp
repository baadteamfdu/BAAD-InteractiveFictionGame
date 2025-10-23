#include <iostream>
#include "Alien.h"

using namespace std;


Alien::Alien() {
	//random starting thresholds
	moveThreshold = rand() % 5 + 2;
	killThreshold = rand() % 3 + 3;
}

//sets isActive to active
void Alien::setActive(bool active) {
	isActive = active;
}

//getter that returns bool isActive
bool Alien::getIsActive() {
	return isActive;
}

//setter for if alien sees the player
void Alien::setSawPlayer(bool seen) {
	sawPlayer = seen;
}

//getter returns bool if alien has seen the player
bool Alien::getSawPlayer() {
	return sawPlayer;
}

//increases the turn counter and accounts for conditions of where player and alien are and if player is at risk: 
void Alien:: increaseTurnCounter(Room * playerCurrentRoom) {
	turnCounter++;
	if (alienCurrentRoom != playerCurrentRoom && sawPlayer == true) { //first, alien and player not in same room but sawPlayer = true, this means player left room with alien in it
		sawPlayer = false; //no longer sees player they left
		idleCounter = 0; //reset idle counter to be nice, they could die instantly while simply checking if alien is in the room. Maybe add peek command?
	}

	if (alienCurrentRoom == playerCurrentRoom && sawPlayer != true) { //if player and alien in same room but alien hasn't seen the player... now it has!
		sawPlayer = true;
		cout << "The alien notices you... run!" << endl; //tell player
	}
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer == true) {	//keep increasing idle counter if player doesn't leave
		idleCounter++; //increments
		if (idleCounter > killThreshold) {
			killPlayer(); //past threshold kill player
			}
	}
	if (turnCounter > moveThreshold && isActive == true && alienCurrentRoom != playerCurrentRoom && sawPlayer != true) { //these might be overkill but it works, basically if not having seen player or in same room and the threshold is passed and the first forced encounter has occured, it can move
		move();
	}
}

//really just a hardcoded method that makes the inital encounter always cryohall, otherwise makes the alien move. This could be one function and not split into leave, in all honesty.
void Alien::move() {
	if (alienCurrentRoom == nullptr) { //first movement (forced later)
		alienCurrentRoom = roomList[1]; //should always be cryohall
		return; //so they don't leave early
	}
	leave();
}

//function to exit the game if they idle too long
void Alien:: killPlayer() {
	cout << "You were caught by the alien" << endl;
	cout << "Game Over" << endl;
	exit(0); //exit function to end the game.
}

//munction to make the alien pick a new room and reset the counters and thresholds (thresholds to random values)
void Alien::leave() {
	Room* moveRoom = alienCurrentRoom; //temp variable
	while (moveRoom == alienCurrentRoom) { //picks a random index until it picks one that isn't the room it is already in to guarantee it moves around to a different room
		moveRoom = roomList[(rand() % roomList.size())];
	}
	sawPlayer = false; //this is kind of a given
	idleCounter = 0;
	turnCounter = 0;
	moveThreshold = (rand() % 5 + 2); //I could skip constructor if I merged move with leave?
	killThreshold = rand() % 3 + 3;
	alienCurrentRoom = moveRoom;
}
 
void Alien::addRoom(Room* newRoom) { //add a room to the list of rooms the alien can see
	roomList.push_back(newRoom);
}