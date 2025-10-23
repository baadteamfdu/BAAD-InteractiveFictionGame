#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
using namespace std;

class Alien {
    public:
        Alien();
        void setActive(bool active); //returns a bool called isActive
        bool getIsActive(); //returns state of alien
        void setSawPlayer(bool seen); //sets state of alien
        bool getSawPlayer(); //returns bool sawPlayer
        void increaseTurnCounter(Room* playerCurrentRoom); //increases value of turns counters
        void move(); //on first(alienCurrentRoom = nullptr) activate it goes to cryoHall set as AliencurrentRoom else leave()
        void killPlayer(); //tell player they lost and exit game
        void leave(); //leave setSawPlayer(false) and determine new slightly random threshold and what the new room will eventually be(maybe dont make it able to enter the same exact room twice in a row)
        void addRoom(Room* newRoom);
private:
        bool isActive = false; //store if alien is active
        bool sawPlayer = false;//store if alien has seen the player
        int turnCounter = 0;   //store a counter for turns to move
        int idleCounter = 0;   //store a counter for idle turns
        int moveThreshold = 1; //store a threshold for movement will be set randomly later
        int killThreshold = 1; //store a threshold for kills will be set randomly later
        Room* alienCurrentRoom = nullptr; //store aliens current Room
        vector<Room*> roomList;
};