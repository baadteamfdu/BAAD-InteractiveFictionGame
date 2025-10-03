#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include <string>
using namespace std;

class Game
{

	public: 
		void init();
		Room * getCurrentRoom();
		Parser getParser();
private:
		void process(Actions action, string noun);
		void showHelp();
		

		Room * currentRoom;
		Parser parser;

		//eventually add a way to delete all the rooms
};

