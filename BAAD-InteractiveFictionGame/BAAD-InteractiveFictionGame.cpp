// BAAD-InteractiveFictionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"
#include <string>
#include "Actions.h"
using namespace std;

int main()
{
    //setup for the game
	Game game;
	game.init();
    cout << "Welcome to <BAAD Game>." << endl; //idk what to call it, No Space is Safe? Play on words? BAAD ALIEN? BAAD SPACE?
    cout << "You wake up from cyrostasis, something has gone very wrong." << endl;  
    cout << "An alien egg was in shipment but hatched during transport." << endl; 
    cout << "You have to make your way through the ship to an escape pod." << endl;
    cout << "Along the way, you should hide in vents, safe rooms, etc." << endl;
    cout << "Type \"help\" for a list of commands." << endl;
    cout << "To get started, try using the look command." << endl << endl;
    //cout << game.getCurrentRoom()->getDescription() << endl;
    string input;

    //running the game by repeatedly asking for input
    while (getline(cin, input)) {
        cout << endl;
        Actions action = Actions::INVALID;
        string noun = "";
        if (input == "help") { //simple way to handle one word commands
            game.getHelp();
            continue;
        }
        if (game.getParser().parse(input, action, noun) == false) { //will detect invalid input otherwise process it
            cout << "Command not understood." << endl;
            continue;
        }
        //game.process(action, noun);
    }
}
