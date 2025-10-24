#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
using namespace std;

class Alien {
    public:
        Alien();
        void setAlienIsACtive(bool active); //  sets alien to be actively roaming the game (true), or disables the alien (false)
        bool isAlienActive(); //returns state of alien - true - alien is roaming the game
        void setAlienHasSeenPlayer(bool seen); // true = alien & player have seen each other, and the player is at risk, set to false when they are in different rooms
        bool hasAlientSeenPlayer(); // returns true if the Alien & player have seen each other (e.g. in same room)
        bool isAlienInTheRoom(Room* roomOfInterest); // LV - returns true if alien is in the passed room, false if not
        void increaseTurnCounter(Room* playerCurrentRoom); //increases value of turns counters - refactor this one & rename
        void moveAlienToANewRoom(); //on first(alienCurrentRoom = nullptr) activate it goes to cryoHall set as AliencurrentRoom else leave()
        void killPlayer(); //tell player they lost and exit game
        void relocateAlienToANewRoom(); //leave setSawPlayer(false) and determine new slightly random threshold and what the new room will eventually be(maybe dont make it able to enter the same exact room twice in a row)
        void addRoom(Room* newRoom);

        // LV - methods to help with testing, likely not proper to have code here, will check - only used for unit testing
        int getNumMovesBeforeAlienChangesRooms() const { return moveThreshold; }  // returns # of turns when alien & player are in different rooms, before the alien changes rooms
        int getNumMovesB4PlayerDies() const { return killThreshold; }       // returns # of turns player & alien need to co-habitate before player dies :(
        string getAliensCurrentRoom() const { return alienCurrentRoom->getId(); }  // returns room identifier (a string) where Alien is currently hiding
        int getTimeInRoomCounter() const { return idleCounter; }                // returns counter of moves alien & player have been co-habitating
        void moveAlienToSpecificRoom(Room* room);   // moves alien to the specified room
private:
        bool isActive = false; //store if alien is active
        bool sawPlayer = false;//store if alien has seen the player
        int turnCounter = 0;   //store a counter for turns to move
        int idleCounter = 0;   //store a counter for idle turns
        int moveThreshold = 1; //store a threshold for movement will be set randomly later
        int killThreshold = 1; //store a threshold for kills will be set randomly later
        Room* alienCurrentRoom = nullptr; //store aliens current Room
        vector<Room*> roomList;

        // LV - helper function to set move & player death thresholds
        void resetAlienRelatedCountersAndThresholds();
};