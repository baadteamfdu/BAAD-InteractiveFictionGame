#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include "Alien.h"
#include <string>
using namespace std;

class Game {
private:
    Room* currentRoom = nullptr;
    Parser parser;
    Inventory inventory;
    Alien alien;
    Object* flashlight;                  // Object flashlight is created here to have access in the gameProcess()
    Object* batteries;                   // Object batteries is created here to have access in the gamePorcess()
    Object* escPodChamDoor;              // To change the state of the door(if open or not) in the gameProcess()
    bool foundcode1 = false;             // code in bathroom set to false by default. to check of the player got the first half.
    bool foundcode2 = false;             // code found in book set to false by default.to check of the player got the second half.
    int passcode;                        // random 4 digit passocde.
    int passcode1;                       //variable to store first half of the passcode.
    int passcode2;                       // variable to store second half of the passcode.
    int runCount = 0;                    //how many times the player has entered run
    bool inEscapeSequence = false;                //true when they enter the final room, tracks point of no return 
    bool controlPanelUnscrewed = false;  // Tracks if the control panel has been unscrewed
    bool firstButtonPressed = false;     // Tracks if the button inside the control panel has been pressed
    bool darkRoomButtonPressed = false; // Tracks if the button in the dark room has been pressed
    vector<Room*> allRooms;             //this vector stores all rooms for the map

    bool playerIsHidden = false;     // flag to check if the player is hidden. Consider creating new player class later.

    // tutorial checks
    bool tutorialEnabled = true;
    bool tutorialLook = true;
    bool tutorialTake = true;
    bool tutorialUnlock = true;
    bool tutorialMove = true;
    bool tutorialReminderToLookAndMove = true; // used after first entering CryoHall
    bool tutorialHide = true;

public:

    void init();
    void process();
    void getHelp();

    Room* getCurrentRoom();
    void setCurrentRoom(Room* nextRoom);

    void peekDoor(const string& doorName); //peek that just checks if next room has alien in it or not and notifies player
    void useKeycard(Object* door);
    void useScrewdriver(Object* vent);
    void goDoor(const string& doorName);
    void typeCode(int enteredCode);
    bool combine(Object* one, Object* two); // to combine two objects

    void displayMap() const; //this code will display the map for the game
    void checkBothButtons();
    void hide(string noun);
	void unhide();
    void pressButton(Object* button);   // new function
	void setIsHidden(bool hidden); // setter for playerIsHidden

    bool getIsHidden(); // getter for playerIsHidden

};