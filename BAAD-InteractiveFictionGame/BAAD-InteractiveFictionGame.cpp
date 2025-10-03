// BAAD-InteractiveFictionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"
#include <string>
using namespace std;

int main()
{
	Game game;
	game.init();
    cout << "Welcome to <BAAD Game>." << endl; //idk what to call it, No Space is Safe? Play on words? BAAD ALIEN? BAAD SPACE?
    cout << "Type \"help\" for a list of commands." << endl << endl;
    cout << game.getCurrentRoom()->getDescription();
    string input;
}
