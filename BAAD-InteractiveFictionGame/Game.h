#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include <string>
using namespace std;

class Game {
private:
    Room* currentRoom = nullptr;
    Parser parser;
    Inventory inventory;

public:
    void init();
    void process();
    void getHelp();

    Room* getCurrentRoom();
    void setCurrentRoom(Room* nextRoom);
};
