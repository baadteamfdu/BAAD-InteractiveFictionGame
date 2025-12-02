// BAAD-InteractiveFictionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include "Game.h"
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include "Actions.h"
# include <stdlib.h> 
using namespace std;

// Function to clear the console screen ..................Credit: https://stackoverflow.com/questions/70687173/how-to-clear-screen-in-c-programming-im-u-using-dev-c-but-everything-i-try-seem
void clearScreen() {
    system("cls");  
}


int main ()
{

    srand(time(0));  // initialize random seed.
    while (true) {
        cout << "======== MAIN MENU ========\n";
        cout << "1. Start Game\n";
        cout << "2. Exit Game\n";
        cout << "> ";
        string choice;
   
        if (!getline(cin, choice)) {
            cout << "input closed exiting game...\n";
            exit(0);
        }

        if (choice == "1") {
            clearScreen();
            PlaySound(TEXT("sfx/startgame"), NULL, SND_FILENAME | SND_ASYNC); //start sound
            break;   // continue into the game
        }
        else if (choice == "2") {
            cout << "Exiting game...\n";
            return 0;
        }
        else {
            cout << "Invalid input. Please type 1 or 2.\n\n";
        }
    }
    //setup for the game
	Game game;
	game.init();
    cout << "Welcome to BAAD Alien Version 4." << endl; 
    cout << "You wake up from cyrostasis, something has gone very wrong." << endl;  
    cout << "An alien egg was in shipment but hatched during transport." << endl; 
    cout << "You have to make your way through the ship to an escape pod." << endl;
    cout << "Along the way, you should hide in vents, safe rooms, etc." << endl;
    cout << "Type \"help\" for a list of commands. They are not actually case sensitive." << endl;
    cout << "To get started, try using the LOOK command on the room. (LOOK AROUND)" << endl << endl;
    //cout << game.getCurrentRoom()->getDescription() << endl;


    //running the game by repeatedly asking for input
    game.process();
    return 0;
 
};
