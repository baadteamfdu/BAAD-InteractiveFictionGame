#pragma once

#include "Actions.h"
#include "Room.h"
#include "Inventory.h"
#include "Captain.h"
#include "Object.h"
#include "Parser.h"
#include "Alien.h"
#include <string>
#include <vector>
using namespace std;

extern int noteCounter; //Global variable so it is possible to access it in the alien.h

class Game {
private:
    //==============================NOTE VARIABLES===============================

    //Note text
    string storageText = "SHIP LOG - Day 47\nDr.Gojo Sami, Lead Xenobiologist"
        "\nThe sample is unstable.More than I anticipated.\nI have documented everything, just in case."
        "\nIf someone finds this, (*something unreadable*)."
        "\nNot everything is as it seems.\nG.S.";

    string mirrorText = "An accident.Could not stop it."
        "\nThey will never understand(not readable)"
        "\nThe answer exists in pieces."
        "\nBeginning holds(water damage)"
        "\nWorkers space holds(torn edge)"
        "\nRecords in the dark will(ink faded)"
        "\nSomeone might remember(blurred section)"
        "\nDont destroy what you dont(rest torn away)";
    
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

    string keycardText =
        "\nA plastic ID card, partially melted and scratched."
        "\nName: DR. (melted plastic obscures first name) SAMI"
        "\nDepartment : XENO(scratched)"
        "\nID : GS - (not readable)"
        "\nClearance : LEVEL(damaged)";

    string cryoHallText =
        "\nBefore cryosleep... there was an accident. One of the "
        "\ndoctors was (he pauses, struggling to remember) running "
        "\nexperiments. Something went wrong in the lab. I heard "
        "\nalarms but... (trails off) can't remember more...";

    string kitchenText =
        "\nI remember someone running past... frantic. They were "
        "\nheading to the (he shakes his head) Dark Room, I think? "
        "\nSaid something about testing on (memory gap). I tried "
        "\nto stop them but... it's all foggy...";

    string workerRoomText =
        "\nThe intercom... someone was screaming. No, not screaming. "
        "\n(long pause) Changing. The voice got deeper, distorted. "
        "\nThey kept saying (he can't recall the exact words) "
        "\nsomething like 'I'm sorry' over and over...";
    string dockRoomText =
        "\nRight before they froze me, I saw (struggles to focus) "
        "\nsecurity footage. Someone... transforming. They left notes "
        "\neverywhere. Scratched something on the walls. Their ID badge "
        "\nwas (memory fades) somewhere in CryoStart. I cannot... "
        "\nI cannot remember the name...";

    string darkText;

    //Actual Note Objects
    Object* storageNote;
    Object* bathroomNote;
    Object* darkNote;
    Object* captainNote;
    Object* alienNote;

    Object* keycard;

   //====================CAPTAIN'S SPEECH========================

    //=======GENERIC SPEECH=====
    string generic1;
    string generic2;
    string generic3;
    string generic4;
    string generic5;

    // ARRAY TO SAVE ALL GENERIC SPEECH TO ONE PLACE, TO NOT TO USE A LOT OF IF STATEMENTS IN THE FUTURE. THIS VALUES MUST ALWAYS BE SO
    string genericText[5];

    //======SPECIAL SPEECH======
    Object* kitchenSpeech;
    Object* workersSpeech;
    Object* cryoHallSpeech;
    Object* dockSpeech;

    //TO CHECK HOW MANY SECREET SPEECHES DID THE USER SEE
    int revealCount;

    //TO STORE IDS FOR SPECIAL ROOMS
    string specialRooms[4];

    //TO CHECK IF THE USER SAW THE SPECIAL SPEECH FROM CAPTAIN IN SPECIAL ROOMS
    bool revealed[4];

    //To store the captains special speech
    Object* captainNoteArr[4];

    //To track how many times the user used flashlight on the note
    int flashlightCounter = 0;

    //================================================================================

    Room* currentRoom = nullptr;
    Parser parser;
    Inventory inventory;
    Alien alien;
    Captain captain;                    
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


    // Note manipulation functions
    bool useMirror(Object* note);
    void createBathroomNote();
    void createDarkNote();
    void lightRevealing();
    void revealInRoom(string roomId);
    void readCapNote();

    // Helper functions for item identification
    bool isNote(string note);
    bool isMirror(string mirror);
    bool isFlashlight(string flash);

    void increaseNoteCounter(Object* obj);

    string takeNoteRoom(string noun); 
};