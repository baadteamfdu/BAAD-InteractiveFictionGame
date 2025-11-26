#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Object.h"
#include "Parser.h"
#include "Alien.h"
#include <string>
using namespace std;

extern int noteCounter; //Global variable so it is possible to access it in the alien.h

class Game {
private:
    // NOTE TEXTS
    string storageText = "SHIP LOG - Day 47\nDr.Gojo Sami, Lead Xenobiologist"
        "\nThe sample is unstable.More than I anticipated.\nI have documented everything, just in case."
        "\nIf someone finds this, (*something unreadable*)."
        "\nNot everything is as it seems.\nG.S.";

    string mirrorText = "An accident.Could not stop it."
        "\n They will never understand(not readable)"
        "\nThe answer exists in pieces."
        "\nBeginning holds(water damage)"
        "\n Workers space holds(torn edge)"
        "\n Records in the dark will(ink faded)"
        "\n Someone might remember(blurred section)"
        "\n Dont destroy what you dont(rest torn away)";
    
    string alienText =
        "[Barely legible, torn and bloodstained paper]\n"
        "\nstill... me...\n"
        "name... Gojo (smudged)\n"
        "\ncannot... fight it... much longer\n"
        "hurts... so much...\n"
        "\n(*large section destroyed by claw marks*)\n"
        "\n you found... notes?\n"
        "YOU KNOW... what I (torn)\n"
        "\nplease... donot run...\n"
        "still... human... inside...\n"
        "\nG.S.\n";

    string darkText;

    int flashlightCounter = 0;

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


    /* VARIABLES FOR NOTES 
    
    counter to check how many notes have been collected, and notes itself so
    it is possible to manipulate them in the gameProcess()
    ==================================
    */

    Object* bathroomNote;
    Object* storageNote;
    Object* darkNote;
    Object* alienNote;

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

    bool useMirror(Object* note); // to reveal the first note in the bathroom

    void createBathroomNote();

    void increaseNoteCounter(Object* obj);

    bool isNote(string note);
    bool isMirror(string mirror);
    bool isFlashlight(string flash);

    void createDarkNote();

    /*
        Function to return exact note depending on the location of the player so user is able to write just take paper to take each note    
    */
    string takeNoteRoom(string noun); 

    void lightRevealing();

};