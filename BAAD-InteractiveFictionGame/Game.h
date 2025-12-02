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

extern int noteCounter;         //Global variable so it is possible to access it in the alien.h
extern bool saveAlien;          //For checking the decision if the player whant to save the alien or not 
class Game {
private:
    //==============================NOTE VARIABLES===============================

    //Note text
    string storageText = "SHIP LOG - Day 47\nDr. Gojo Sami, Lead Xenobiologist"
        "\nThe sample is unstable, more than I anticipated.\nI have documented everything just in case."
        "\nIf someone finds this, (*something unreadable*)."
        "\nNot everything is as it seems.\nG.S.";

    string mirrorText = "An accident. Could not stop it."
        "\nThey will never understand(not readable)"
        "\nThe answer exists in pieces."
        "\nBeginning holds(water damage)"
        "\nWorkers space holds(torn edge)"
        "\nRecords in the dark will(ink faded)"
        "\nSomeone might remember(blurred section)"
        "\nDo not destroy what you do not(rest torn away)";
    
    string alienText =
        "[Barely legible, torn and bloodstained paper]\n"
        "\nstill... me...\n"
        "name... Gojo (smudged)\n"
        "\ncannot... fight it... much longer\n"
        "hurts... so much...\n"
        "\n(*large section destroyed by claw marks*)\n"
        "\n you found... notes?\n"
        "YOU KNOW... what I (torn)\n"
        "\nplease... do not run...\n"
        "still... human... inside...\n"
        "\nG.S.\n";

    string keycardText = "\nA plastic ID card, partially melted and scratched."
        "\nName: DR. (melted plastic obscures first name) SAMI"
        "\nDepartment: XENO(scratched)"
        "\nClearance: LEVEL(damaged)"
        "\nID: GS - ";



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

    /*====================
    * ENDING VARIABLES
    =====================*/

    bool hasReadLastNote;   //To let the user talk to captain
    bool hasDecision;       //

    string captainMemoryDialogue =
        "You approach the Captain. His eyes widen.\n"
        "\"...You found them. All of them.\"\n\n"
        "He slowly flips through the notes. With every page, his face drains of color.\n"
        "\"Gojo... His name was Gojo. One of our lead genetic engineers.\n"
        "Brilliant. Reckless. He volunteered for the genome tests, said he could push our evolution forward.\"\n\n"
        "He presses a shaking hand to his forehead.\n"
        "\"But the experiment failed. His body twisted... his mind fractured.\n"
        "We locked him away, hoping the serum would work. Hoping he'd come back.\"\n\n"
        "He looks directly at you.\n"
        "\"That creature stalking us... it's Gojo. What's left of him.\"\n\n"
        "A long silence follows.\n"
        "\"There *is* a cure. One final vial. Hidden in a locked chest inside the kitchen vent.\n"
        "Gojo made me promise we'd try to save him if the worst happened.\"\n\n"
        "The Captain steps closer.\n"
        "\"So now you know the truth. And I need your answer. Right now.\"\n\n";

    string captainYesDialogue =
        "Captain: \"...You really want to save him?\"\n"
        "He nods slowly. \"Alright. Then listen. I remembered something, there's a vent in the kitchen.\"\n"
        "\"Inside it is a Nano Locker. We hid a genome-reversal serum inside before everything went to hell.\"\n"
        "\"Unscrew the vent, find the locker, and use the password from the keycard to open it.\"\n"
        "\"When the alien finds you, throw the cure at him. Aim center mass. You will only get one chance.\"\n"
        "He meets your eyes. \"If Gojo is still in there... bring him back.\"\n";

    string captainNoDialogue =
        "Captain: \"...I see. You don’t want to risk it.\"\n"
        "He looks away, jaw tight. \"Maybe you're right. Maybe Gojo is gone for good.\"\n"
        "\"We focus on surviving now. When we reach the escape pod, we leave him behind.\"\n"
        "\"Come on. Let's finish this.\"\n";

    Room* kitchenVent;
    Object* nanoLocker;
    Object* cure;

    Room* kitchen;

    Object* kitchenVentDoor;

    int nanoLockerPasscode;

    Captain gojo;

    string genericTextGj[7];

    string genericGj1;
    string genericGj2;
    string genericGj3;
    string genericGj4;
    string genericGj5;
    string genericGj6;
    string genericGj7;


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


    void specialDialogueCap();

    void openNanoLocker();
    void typeCodeNanoLocker(int passcode);

    void throwCure();

    void happyEnding();

    void talkGojo();
};