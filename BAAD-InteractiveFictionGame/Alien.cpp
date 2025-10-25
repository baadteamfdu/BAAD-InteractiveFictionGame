#include <iostream>
#include "Alien.h"

using namespace std;

// Who sets the alien to active?


Alien::Alien() {
	resetAlienRelatedCountersAndThresholds();  // movement, player death, counters & player/alien co-habitation status
}


// //sets isActive to active
// will we ever reset the IsActive flag - if so, maybe use another method? - e.g. setAlientToActive() & setAlienToInactive()
void Alien::setAlienIsACtive(bool active) {
	isActive = active;
}

// LV - can do better on the comments - e.g. returns if Alien is actively trolling the dungeon
//    if Alien is active, then it is in a room
//getter that returns bool isActive
bool Alien::isAlienActive() {
	return isActive;
}

//setter for if alien sees the player
void Alien::setAlienHasSeenPlayer(bool seen) {
	sawPlayer = seen;
}

//getter returns bool if alien has seen the player
bool Alien::hasAlientSeenPlayer() {
	return sawPlayer;
}

// LV - returns true if alien is in the passed room, false if not
bool Alien::isAlienInTheRoom(Room * playerCurrentRoom) {
	if (alienCurrentRoom == playerCurrentRoom)
		return true;
	else
		return false;
}

//increases the turn counter and accounts for conditions of where player and alien are and if player is at risk: 
// LV - does more than just increase the turn counter, more like Alien move & encounter
//   if alien in a room for longer than 
void Alien:: increaseTurnCounter(Room * playerCurrentRoom) {
	turnCounter++;
	// LV - why check sawPlayer?  if not in the same room as the alien, ..., but given reset when moving rooms, redundant, but ok
	if (alienCurrentRoom != playerCurrentRoom && sawPlayer == true) { //first, alien and player not in same room but sawPlayer = true, this means player left room with alien in it
		sawPlayer = false; //no longer sees player they left
		idleCounter = 0; //reset idle counter to be nice, they could die instantly while simply checking if alien is in the room. Maybe add peek command?
	}

	// LV - consider the following
	// if alien not in the same room
	//   ....
	// else alien is in the same room
	//   if alien or player just entered the room ie !hasAlienSeenPlayer()
	//      player has been seen (e.g. setAlienHasSeenPlayer(true);  alternatively, break into setAlienHasSeenPlayer() & resetAlienHasSeenPlayer()
	//        (note: idlecounter = 0 when player & alien first encounter each other, should be documented)
	//   else   player & alien have been in the room for > 1 turn
	//      if player & alien in room together for greater than randomly set # of turns, player dies
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer != true) { //if player and alien in same room but alien hasn't seen the player... now it has!
		sawPlayer = true;
		cout << "The alien notices you... run!" << endl; //tell player
	}
	if (alienCurrentRoom == playerCurrentRoom && sawPlayer == true) {	//keep increasing idle counter if player doesn't leave
		idleCounter++; //increments
		if (idleCounter > killThreshold) {
			killPlayer(); //past threshold kill player, LV - note this exits the game, no return from here, consider should this be part of the Alien class?
			}
	}

	// LV - this needs a better comment
	//   e.g. turnCounter is really alienTurnsInARoom
	//   as long as the alien isn't in the same room as the player, if > than the threshold, move to another room
	if (turnCounter > moveThreshold && isActive == true && alienCurrentRoom != playerCurrentRoom && sawPlayer != true) { //these might be overkill but it works, basically if not having seen player or in same room and the threshold is passed and the first forced encounter has occured, it can move
		moveAlienToANewRoom();
	}
}

//really just a hardcoded method that makes the inital encounter always cryohall, otherwise makes the alien move. This could be one function and not split into leave, in all honesty.
void Alien::moveAlienToANewRoom() {

	if (alienCurrentRoom == nullptr) { //first movement (forced later)
		alienCurrentRoom = roomList[1]; //should always be cryohall
		return; //so they don't leave early
	}
	cout << "relocating alien \n";
	relocateAlienToANewRoom();
}

//function to exit the game if they idle too long
void Alien:: killPlayer() {
	cout << "You were caught by the alien" << endl;
	cout << "Game Over" << endl;
	exit(0); //exit function to end the game.
}

//function to make the alien pick a new room and reset the counters and thresholds (thresholds to random values)
void Alien::relocateAlienToANewRoom() {

	// LV - randomly pick a new room for the alien that is not the current room
	Room* moveRoom = alienCurrentRoom; //temp variable
	while (moveRoom == alienCurrentRoom) { //picks a random index until it picks one that isn't the room it is already in to guarantee it moves around to a different room
		moveRoom = roomList[(rand() % roomList.size())];
	}  // LV - this probably goes into an infinite loop if only one room in the room list, should check if roomList.size() == 1, if so, leave alien in the current room

	alienCurrentRoom = moveRoom;
	// LV - refactored to use helper function
	resetAlienRelatedCountersAndThresholds();
}
 
void Alien::addRoom(Room* newRoom) { //add a room to the list of rooms the alien can see
	roomList.push_back(newRoom);
}

// LV - helper function to set move & player death thresholds
void Alien::resetAlienRelatedCountersAndThresholds() {
	moveThreshold = (rand() % 5 + 2);
	killThreshold = rand() % 3 + 3;
	idleCounter = 0;
	turnCounter = 0;
	setAlienHasSeenPlayer(false);
}

// test function to move the alien to the specified room
void Alien::moveAlienToSpecificRoom(Room* room) {
	alienCurrentRoom = room;
	resetAlienRelatedCountersAndThresholds();
}
