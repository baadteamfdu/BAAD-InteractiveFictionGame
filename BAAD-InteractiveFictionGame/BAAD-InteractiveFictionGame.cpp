// BAAD-InteractiveFictionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"
#include <string>
#include "Actions.h"
using namespace std;

int main()
{

    srand(time(0));  // initialize random seed.
    //setup for the game
	Game game;
	game.init();
    cout << "Welcome to BAAD Alien Version 3." << endl; 
    cout << "You wake up from cyrostasis, something has gone very wrong." << endl;  
    cout << "An alien egg was in shipment but hatched during transport." << endl; 
    cout << "You have to make your way through the ship to an escape pod." << endl;
    cout << "Along the way, you should hide in vents, safe rooms, etc." << endl;
    cout << "Type \"help\" for a list of commands." << endl;
    cout << "To get started, try using the look command." << endl << endl;
    //cout << game.getCurrentRoom()->getDescription() << endl;


    //running the game by repeatedly asking for input
    game.process();
    return 0;
 
};
