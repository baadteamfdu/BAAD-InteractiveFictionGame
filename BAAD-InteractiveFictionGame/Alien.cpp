#include <iostream>
#include "Alien.h"

using namespace std;


Alien::Alien() {
	resetAlienState();
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
void Alien::increaseTurnCounter(Room* playerCurrentRoom, bool isHidden) {
	if (isActive == true) {
		turnCounter++;

		if (alienCurrentRoom == playerCurrentRoom && sawPlayer != true) { //if player and alien in same room but alien hasn't seen the player... now it has!
			sawPlayer = true;
			cout << "The alien notices you... run and hide!" << endl; //tell player
		}
		if (sawPlayer == true) { //factored out saw player
			chaseCounter++;
			if (alienCurrentRoom == playerCurrentRoom && isHidden && chaseCounter < chaseThreshold) { //same room and hid in time
				cout << "The alien enters the room, looks around.... then leaves" << endl;
				leave(); //if alien and player in same room but player is hidden, alien leaves
				return;
			}
			if (alienCurrentRoom != playerCurrentRoom) { //alien and player not in same room but sawPlayer = true, this means player left room with alien in it
				alienCurrentRoom = playerCurrentRoom; //alien follows player to new room
				cout << "You hear the alien close behind you... run and hide!" << endl;
			}
			if (alienCurrentRoom == playerCurrentRoom && chaseCounter >= chaseThreshold && isHidden) {	//keep increasing chase counter if player doesn't leave but if they hide on the last turn possible they die
				cout << "The alien pulls you out of the locker, if only you had hidden sooner." << endl;
				killPlayer(); //past threshold kill player
				return;
			}
			if (alienCurrentRoom == playerCurrentRoom && chaseCounter >= chaseThreshold && !isHidden) {	//keep increasing chase counter if player doesn't hide
				cout << "You failed to hide in time." << endl;
				killPlayer(); //past threshold kill player
				return;
		}
	}
		
		//move if not chasing
		if (turnCounter > moveThreshold && isActive == true && alienCurrentRoom != playerCurrentRoom && sawPlayer != true) { //these might be overkill but it works, basically if not having seen player or in same room and the threshold is passed and the first forced encounter has occured, it can move
			move();
		}
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
void Alien::killPlayer() {
	cout << "You were caught by the alien." << endl;
	cout << "Game Over" << endl;
	exit(0); //exit function to end the game.
}

//munction to make the alien pick a new room and reset the counters and thresholds (thresholds to random values)
void Alien::leave() {
	Room* moveRoom = alienCurrentRoom; //temp variable
	while (moveRoom == alienCurrentRoom) { //picks a random index until it picks one that isn't the room it is already in to guarantee it moves around to a different room
		moveRoom = roomList[rand() % roomList.size()];
	}
	alienCurrentRoom = moveRoom;
	resetAlienState();
}
 
void Alien::addRoom(Room* newRoom) { //add a room to the list of rooms the alien can see
	roomList.push_back(newRoom);
}

void Alien::resetAlienState() { //taken from professor's recommendation
	moveThreshold = (rand() % 5) + 2;
	chaseThreshold = (rand() % 3) + 6;
	turnCounter = 0;
	chaseCounter = 0;
	sawPlayer = false;
}