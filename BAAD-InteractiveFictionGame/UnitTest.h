#pragma once
#include "game.h"
#include "Alien.h"

class UnitTest
{
public:
	// initially - let's do some unit testing of the alien class
	//   will test a few scenarios & output to console
	void alienTest();

private:
    void setupAlienRooms(Alien& alien);

    // I don't like this - but the room list is not stored anywhere, so let's re-initialize the rooms for testing
    // Create rooms
    Room* cryoStart = new Room(
        "cryo01",
        "Cryo Chamber",
        "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n"
    );
    Room* cryoHall = new Room(
        "cryoHall",
        "Cryo Hallway",
        "A long hallway with doors on either side. The lights flicker occasionally.\n"
    );
    Room* escapePod = new Room(
        "escapePod",
        "Escape Pod Chamber",
        "A small room with blinking lights and a sealed escape pod. The others appear broken. \n"
    );
    Room* workersRoom = new Room(
        "workersRoom",
        "Worker's Room",
        "A small room with bunks and personal lockers for the station's crew.\n"
    );
    Room* bathroom = new Room(
        "bathroom",
        "Bathroom",
        "A small, sterile bathroom with a sink and a mirror.\n"
    );
    Room* finalRoom = new Room(
        "finalRoom",
        "Abandoned Control Room",
        "The control room is dark and silent, with flickering monitors and empty chairs.\n"
    );
};

