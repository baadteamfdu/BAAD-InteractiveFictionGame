// BAAD-InteractiveFictionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"
#include <string>
#include "Actions.h"
using namespace std;

int main()
{
	Game game;
	game.init();
    cout << "Welcome to <BAAD Game>." << endl; //idk what to call it, No Space is Safe? Play on words? BAAD ALIEN? BAAD SPACE?
    cout << "Type \"help\" for a list of commands." << endl << endl;
    //NOTE PRINT DESCRIPTION AND MAYBE ADD A HINT TO USE LOOK
    cout << game.getCurrentRoom()->getDescription();
    string input;
    while (getline(cin, input)) {
        cout << endl;
        Actions action = Actions::INVALID;
        string noun;
        if (input == "help") { //simple way to handle one word commands
            game.getHelp();
            continue;
        }
        if (game.getParser().parse(input, action, noun) == false) {
            cout << "Command not understood." << endl;
            continue;
        }
        //game.process(action, noun);
    }
}
