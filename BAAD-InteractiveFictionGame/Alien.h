#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
using namespace std;

class Alien {
    public:
        Alien();
        bool isAlienInRoom(Room * playerCurrentRoom);
        void setActive(bool active); //returns a bool called isActive
        bool getIsActive(); //returns state of alien
        void addAllRooms(vector<Room*> allRooms);
        void increaseTurnCounter(Room* playerCurrentRoom, bool isHidden); //increases value of turns counters
        void addRoom(Room* newRoom);
        void move(); //on first(alienCurrentRoom = nullptr) activate it goes to cryoHall set as AliencurrentRoom else leave()
        bool getSawPlayer(); //returns bool sawPlayer
        void killPlayer(); //tell player they lost and exit game
        void setCurrentRoom(Room* room) { alienCurrentRoom = room; } // to change aliens location outside the class
        Room* getCurrentRoom() const { return alienCurrentRoom; }
private:
        bool isActive = false; //store if alien is active
        bool sawPlayer = false;//store if alien has seen the player
        int turnCounter = 0;   //store a counter for turns to move
        int chaseCounter = 0; //counter for turns spent chasing
        int moveThreshold = 1; //store a threshold for movement will be set randomly later
        int chaseThreshold = 1; //store a threshold for chasing before killing that will be set randomly later
        Room* alienCurrentRoom = nullptr; //store aliens current Room
        vector<Room*> roomList;
        void setSawPlayer(bool seen); //sets state of alien
        void leave(); //leave setSawPlayer(false) and determine new slightly random threshold and what the new room will eventually be(maybe dont make it able to enter the same exact room twice in a row)
        void resetAlienState(); // resets thresholds and counters
};