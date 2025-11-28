#include "Game.h"
#include "Room.h"
#include "Object.h"
#include "Inventory.h"
#include "Parser.h"   // make sure this exists; otherwise comment this and use the fallback enum below
#include "Alien.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int noteCounter = 0;

// If your Actions enum lives elsewhere, include it there.
// If not, uncomment this fallback:
// enum class Actions { HELP, LOOK, TAKE, INVENTORY };

// https://stackoverflow.com/questions/16884607/character-by-character-output-to-simulate-a-typing-effect
void coolTyping(string text) {
    for (char letter : text) {
        cout << letter;
            this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void Game::init() {



    

    // sets current room to the starting room and initializes the starting room to exist
    // Create rooms

    passcode = rand() % 9000 + 1000; // since there could only be 9000 odds for a four digit passcode and it would start from 1000.
    passcode1 = passcode / 100;      // stores the first two digits for passcode1
    passcode2 = passcode % 100;      // stores the last two digits for passcode 2

    // assigning the booleans false by default. obviously passcode would not be found at the begining.
    foundcode1 = false;
    foundcode2 = false;

	playerIsHidden = false;          // player is not hidden at the start of the game.
    captain.reset(); // captain resets each game.

    // Create rooms
    Room* cryoStart = new Room(
        "cryo01",
        "Cryo Chamber",
        "The air is cold. Behind the glass of the other cryo pods rests people, frozen and silent.\n"
    );
    Room* cryoHall = new Room(
        "cryoHall",
        "Cryo Hallway",
        "A long hallway with doors on either side. The lights flicker occasionally.\n"
    );
    Room* storageArea = new Room(
        "storageArea",
        "Storage Bay",
        "Crates and metal containers are stacked neatly, though a few have been forced open. The air smells faintly of oil and dust.\n"
    );
    Room* dock = new Room(
        "dock",
        "Docking Control Room",
        "A narrow control chamber with terminals and broken screens.\n"
    );
    Room* escapePodChamber = new Room(
        "escapePodChamber",
        "Escape Pod Chamber",
        ""
    );
    Room* finalRoom = new Room(
        "finalRoom",
        "Escape Pod",
        "The control room is dark and silent, with flickering monitors and empty chairs.\n"
    );
    Room* workersRoom = new Room(
        "workersRoom",
        "Worker's Room",
        "A small room with bunks and personal lockers for the station's crew.\n"
    );
    Room* bathroom = new Room(
        "bathroom",
        "Bathroom",
        "A small, sterile bathroom with a sink and a mirror.\n"
    );
    Room* cafeteria = new Room(
        "cafeteria",
        "Cafeteria",
        "Rows of metal tables fill the room. Trays and utensils lie scattered, as if everyone left in a hurry.\n"
    );
    Room* kitchen = new Room(
        "kitchen",
        "Galley Kitchen",
        "Metal counters are smeared with dried food paste. A broken vent hisses softly, filling the air with the smell of burnt plastic.\n"
    );
    Room* darkRoom = new Room(
        "darkRoom",
        "Dark Room",
        "The room is dark and quiet\ You cannot see anything"
    );
      // captain's quarter
    Room* captainRoom = new Room(
        "captainRoom",
        "Captain's Quarters",
        "A small, private cabin dominated by a reinforced cryo pod A reinforced cryo pod rests at the center of the room,\n" 
        "its frosted glass trembling with a faint breath from within and a worn chair sits nearby as if someone waited here long ago.\n"
        );

    setCurrentRoom(cryoStart);

    // Add objects to starting room

    //NOTE ALL OBJECTS MUST HAVE LOWERCASE NAMES AT LEAST FOR NOW, AS TOLOWER IS IN PARSER
    // Add objects to starting room
    //control panel in the cryostart
    Object* controlPanel = new Object("control panel", "A sealed control panel is mounted on the wall.", false, true);
    cryoStart->addObject(controlPanel);

    Object* keycard = new Object("keycard", "A Level A access card with a magnetic stripe.", true, false);
    cryoStart->addObject(keycard);

    // Book in worker's room
    Object* book = new Object("book", "An old logbook", true, false); // creating a book object
    workersRoom->addObject(book); //placing that book in the workers woom. Offcourse is takeable

    //Screwdriver in storage area
    Object* screwdriver = new Object("screwdriver", "A small screwdriver. Could be handy.", true, false);
    storageArea->addObject(screwdriver);

    //vent in storage area (locked by default)
    Object* vent = new Object("vent", "A metal vent cover, screwed & shut.", false, true);
    storageArea->addObject(vent);

    //locker in kitchen
    Object* kitchenLocker = new Object("locker", "A tall kitchen locker with enough space to hide inside.", false, false, true);
    kitchen->addObject(kitchenLocker);

    // stall in bathroom
    Object* stall = new Object("stall", "Looks like it has been dead for a while It might open", false, true);  // creating a stall object.
    stall->setIsOpen(false);
    bathroom->addObject(stall); // Placing in the bathroom.

    //Flashlight in the cafeteria
    flashlight = new Object("flashlight", "A flashlight that does not have batteries", true, false, 0);
    cafeteria->addObject(flashlight);

    //Batteries in the Kitchen
    batteries = new Object("batteries", "Batteries that can be used with flashlight", true, false);
    kitchen->addObject(batteries);

    // Button in the dark room
    Object* buttonDarkRoom = new Object("button", "Button that may open something interesting", false, false);
    darkRoom->addObject(buttonDarkRoom);


    //code halves inside objects 
  //  Object* codePart1 = new Object("code part 1", "Half of the passcode: '--" + to_string(passcode % 100) + "'", true);
  //  Object* codePart2 = new Object("code part 2", "Half of the passcode: '" + to_string(passcode / 100) + "--'", true);
  

    // Creating doors
    Object* cryoDoor = new Object("cryo door", "A door with a card reader", false, true); //cryo card door
    // passcode door
    Object* passcodeDoor = new Object("passcode door", "A door with a keypad lock", false, true); // added the passcode door object.
    passcodeDoor->setIsPasscodeLocked(true); // door is locked
    passcodeDoor->setPasscode(passcode);

    Object* dockDoor = new Object("dock door", "A door to the Dock Room", false, true);
    escPodChamDoor = new Object("escape pod door", "A door to the Escape Pod Door", false, false); //
    Object* finalRoomDoor = new Object("pod door", "A door to the Final Room", false, true);
    Object* workersDoor = new Object("worker door", "A door to the Worker’s Room", false, false);
    Object* bathroomDoor = new Object("bathroom door", "A door to the Bathroom", false, false);
    Object* cafeteriaDoor = new Object("cafeteria door", "A door to the Cafeteria", false, true);
    Object* captainDoor = new Object("captain door", "A door to the Captain's Quarters", false, false);
    Object* kitchenDoor = new Object("kitchen door", "A door to the Kitchen", false, true);
    Object* darkDoor = new Object("dark door", "A door to the Dark Room", false, true);

    // Adding doors to rooms

    cryoStart->addObject(cryoDoor);
    cryoHall->addObject(cryoDoor);

    cryoHall->addObject(passcodeDoor);    //adding the passcode door
    storageArea->addObject(passcodeDoor);

    storageArea->addObject(dockDoor);
    dock->addObject(dockDoor);

    dock->addObject(escPodChamDoor);
    escapePodChamber->addObject(escPodChamDoor);

    escapePodChamber->addObject(finalRoomDoor);
    finalRoom->addObject(finalRoomDoor);

    cryoHall->addObject(workersDoor);
    workersRoom->addObject(workersDoor);

    workersRoom->addObject(bathroomDoor);
    bathroom->addObject(bathroomDoor);

    cryoHall->addObject(cafeteriaDoor);
    cafeteria->addObject(cafeteriaDoor);

    cafeteria->addObject(kitchenDoor);
    kitchen->addObject(kitchenDoor);

    cafeteria->addObject(darkDoor);
    darkRoom->addObject(darkDoor);

    cafeteria->addObject(captainDoor);
    captainRoom->addObject(captainDoor);

    //Connect rooms
    cryoStart->setNeighbour("cryo door", cryoHall);
    cryoHall->setNeighbour("cryo door", cryoStart);

    cryoHall->setNeighbour("passcode door", storageArea);
    storageArea->setNeighbour("passcode door", cryoHall);

    storageArea->setNeighbour("dock door", dock);
    dock->setNeighbour("dock door", storageArea);

    dock->setNeighbour("escape pod door", escapePodChamber);
    escapePodChamber->setNeighbour("escape pod door", dock);

    escapePodChamber->setNeighbour("pod door", finalRoom);
    finalRoom->setNeighbour("pod door", escapePodChamber);

    cryoHall->setNeighbour("worker door", workersRoom);
    workersRoom->setNeighbour("worker door", cryoHall);

    workersRoom->setNeighbour("bathroom door", bathroom);
    bathroom->setNeighbour("bathroom door", workersRoom);

    cryoHall->setNeighbour("cafeteria door", cafeteria);
    cafeteria->setNeighbour("cafeteria door", cryoHall);

    cafeteria->setNeighbour("kitchen door", kitchen);
    kitchen->setNeighbour("kitchen door", cafeteria);

    cafeteria->setNeighbour("dark door", darkRoom);
    darkRoom->setNeighbour("dark door", cafeteria);

    cafeteria->setNeighbour("captain door", captainRoom);
    captainRoom->setNeighbour("captain door", cafeteria);

    allRooms = { cryoStart, cryoHall, storageArea, dock, escapePodChamber, finalRoom, workersRoom, bathroom, cafeteria, kitchen, darkRoom };
    cryoStart->setPosition(24, 0);

    cryoHall->setPosition(7, 2);
    workersRoom->setPosition(8, 2);
    storageArea->setPosition(6, 2);
    dock->setPosition(5, 2);

    cafeteria->setPosition(12, 4);
    bathroom->setPosition(13, 4);
    kitchen->setPosition(11, 4);
    escapePodChamber->setPosition(5, 3);

    darkRoom->setPosition(25, 5);
    finalRoom->setPosition(2, 4);
    // Hiding Object
	Object* safeZone = new Object("locker", "A metal locker large enough to hide inside", false, false, true); // creating a locker object as a safe zone

	workersRoom->addObject(safeZone); // placing the locker in the worker's room
    //let Alien Access rooms
    alien.addAllRooms(allRooms);


    /*
    * giving the values for the NOTES FOR THE LORE.
    */
    darkNote = new Object("note-3", "Note that was found in the Dark Room", true, false);
    bathroomNote = new Object("note-2", "Note that was found in the Bathroom", true, false);
    storageNote = new Object("note-1", "Note that was found in the Dock", true, false);
    storageNote->setNoteText(storageText);
    alienNote = new Object("note-5", "Note that felt from the Alien", true, false);
    alienNote->setNoteText(alienText);

    // JUST ADD FOR NOW MAYBE I WILL COME UP WITH BETTER IDEA TO HIDE IT IN THE FUTURE, HOWEVER I ASSUME THAT THE USING OF FLASHLIGHT IS GOOD ENOUGH
    //darkRoom->addObject(darkNote); 

    }

Room* Game::getCurrentRoom() {
    return currentRoom;
}

void Game::setCurrentRoom(Room* nextRoom) {
    if (nextRoom->getId() == "escapePodChamber" && inEscapeSequence == false) {
        inEscapeSequence = true;
        runCount = 0;
        alien.setActive(false);
        cout << "ENTER RUN! THE ALIEN IS RIGHT BEHIND YOU!" << endl;
    }

    currentRoom = nextRoom;
    //activates alien once player enters cryohall for the first time, I don't know a better way
    if (currentRoom->getId() == "cryoHall" && (alien.getIsActive() == false)) {
        alien.setActive(true);
        alien.move();
        cout << "You see a passcode door on one side, and a door with a broken keycard reader that is lodged open on the other. It leads to a room for workers. There is also a card locked door to the cafeteria." << endl; //hint to tell player to hide and they don't need to use keycard
    }

}

void Game::getHelp() { // prints out available commands
    cout << "Available commands:\n";
    cout << "go <door name>       : move between rooms\n";
    cout << "take <item>\n";
    cout << "use <item> <door name> \n";
    cout << "open <door name> (or <object name>) \n";
    cout << "look <item> (must be inside inventory)\n";
    cout << "look around / look room\n";
    cout << "inventory / look inventory\n";
    cout << "type <passcode>\n";
    cout << "peek <door name>\n";
	cout << "hide <object name>\n";
	cout << "unhide\n";
    cout << "help\n";
    cout << "wake captain\n";
    cout << "note, some common synonyms are supported \n";
}

void Game::peekDoor(const string& doorName) { //borrowed goDoor code

    Object* door = currentRoom->getObject(doorName); //check if the door exists in the current room
    if (!door) {
        cout << "There is no " << doorName << " here.\n";
        return;
    }
    if (door->isTakeable()) { //stop player trying to open or go a keycard
        cout << "You can not peek through this. \n";
        return;
    }
    if (alien.getSawPlayer()) {
        cout << "There is no time for that now!" << endl;
        return;
    }

    Room* nextRoom = currentRoom->getNeighbour(doorName); // get the neighbouring room through the door
    if (nextRoom) {
        if (alien.isAlienInRoom(nextRoom)) { //if alien is in the next room, warn player
            cout << "You peek through the door, only to see something moving on the other side! Wait for it to leave!" << endl;
        }
        else {
            cout << "You peek through the door, there is nothing there and it is safe." << endl; //otherwise tell them there is nothing there
        }
    }
    else {
        cout << "There is no room connected to this door." << endl; //this is a silly check why do we have this in goDoor?
    }
}

//this functions displays the map that is used for the game.
//
void Game::displayMap() const
{
    if (allRooms.empty()) 
    {
        cout << "No map available.\n";
        return;
    }

  
    //builds the label for the room
    auto labelFor = [&](Room* r) 
        {
        if (currentRoom && currentRoom->getId() == r->getId())
            return "[" + r->getName() + "*]"; //adds the star if the player is in the room
        else
            return "[" + r->getName() + "]"; //no star means player is not in room
        };

    // Find the smallest and largest X & Y positions
    // so the map prints only a little bit of used space
    int minX = 1000000, minY = 1000000;
    int maxX = -1000000, maxY = -1000000;
    for (Room* r : allRooms) 
    {
        if (!r) continue;
        if (r->getX() < minX) minX = r->getX();
        if (r->getX() > maxX) maxX = r->getX();
        if (r->getY() < minY) minY = r->getY();
        if (r->getY() > maxY) maxY = r->getY();
    }

    //This code tells us how many rows and columns are needed for the grid
    int rows = maxY - minY + 1;
    int cols = maxX - minX + 1;

    //This is the grid itself!
    vector<vector<string>> grid(rows, vector<string>(cols, "."));

    // --- place labels ---
    for (Room* r : allRooms) 
    {
        if (!r) continue;
        // Convert actual game coordinates into grid indexes
        int gx = r->getX() - minX;
        int gy = r->getY() - minY;
        if (gx < 0 || gx >= cols || gy < 0 || gy >= rows) continue;
        grid[gy][gx] = labelFor(r);
    }

    // This prints the grid from top to bottom!
    cout << "\n--- MAP ---\n\n";
    for (int rr = rows - 1; rr >= 0; --rr) 
    {
        for (int cc = 0; cc < cols; ++cc) 
        {
            cout << grid[rr][cc] << " ";
        }
        cout << "\n";
    }
    cout << "\n* = You\n\n";
}


/*  void Game::checkBothButtons()
*
*
================*********================================

Either says just one button has been pressed, or both
If both were pressed it will unlock escPodChamDoor
*/


void Game::checkBothButtons() {
    if (firstButtonPressed && darkRoomButtonPressed) {
        escPodChamDoor->setIsLocked(false);
        cout << "You hear a heavy clang from afar... The escape pod chamber door unlocks!\n";
    }
    else {
        cout << "Something activated... but it seems another system still needs power.\n";
    }
}



/*  void Game::pressButton(Object* button)
* 
* 
================*********================================


Handles the player's attempt to press a button in the game.
- Checks if the object exists; if not, shows an error message.
- Ensures the object is actually a "button" before allowing interaction.
- Prevents repeated presses using the firstButtonPressed flag.
- On the first valid press, sets the flag to true and displays a message
  indicating that something in the station has been activated.
*/

    void Game::pressButton(Object * button)
    {
        if (!button)
        {
            cout << "There’s no button here to press.\n";
            return;
        }

        if (button->getName() != "button")
        {
            cout << "You can’t press that.\n";
            return;
        }

        // If in CryoStart room -> Control Panel button
        if (currentRoom->getId() == "cryo01")
        {
            if (firstButtonPressed)
            {
                cout << "You already pressed the control panel button. Nothing happens.\n";
                return;
            }

            firstButtonPressed = true;
            cout << "You press the control panel button. A faint hum echoes through the station.\n";
            checkBothButtons();
            return;
        }

        // If in Dark Room Override button
        if (currentRoom->getId() == "darkRoom")
        {
            if (flashlight->getIsWorking() == false) {
                cout << "The room is too dark, you cannot see anything.\n";
                return;
            }

            if (darkRoomButtonPressed)
            {
                cout << "You already pressed the override button.\n";
                return;
            }

            darkRoomButtonPressed = true;
            cout << "You press the override button. A mechanical hum echoes faintly.\n";

            // Only open the escape pod if both buttons pressed
            checkBothButtons();
            return;
        }

        cout << "You press the button, but nothing seems to happen here.\n";
    }



/* void Game::useScrewdriver(Object* obj)
* *************************===============*******************************
* 
* 
Handles the player's action when using the screwdriver on an object.

- Checks if the target object exists; if not, notifies the player.
- If used on the "vent":
    • Unlocks it if it’s closed and marks it as a safe zone where the player can hide.
    • If already open, informs the player that nothing needs to be done.
- If used on the "control panel":
    • Ensures it hasn’t been opened before using the controlPanelUnscrewed flag.
    • When first opened, a hidden "button" object is created and added to the room.
      (The button is created here because it represents a new interactive element
       that only becomes accessible after the player unscrews the control panel.)
    • Displays a message indicating that the button has been revealed.
- If used on anything else, informs the player that the screwdriver has no effect.
*/



void Game::useScrewdriver(Object* obj)
{
    if (!obj) {
        cout << "There's nothing like that to use the screwdriver on.\n";
        return;
    }

    string name = obj->getName();

    if (name == "vent") {
        if (!obj->getIsLocked()) {
            cout << "The vent is already open.\n";
            return;
        }
        obj->setIsLocked(false);
        obj->setIsSafeZone(true);
        cout << "As you quietly unscrew the vent cover, a small piece of paper slips out and falls to the floor.\n You could probably hide inside now.\n";
        //ADD NOTE TO THE Room
        currentRoom->addObject(storageNote);
        return;
    }
    if (name == "control panel") {
        if (controlPanelUnscrewed) {
            cout << "The control panel is already open.\n";
            return;
        }


        controlPanelUnscrewed = true;
        Object* button = new Object(
            "button", "A small red button inside the open control panel.", false, false);
        currentRoom->addObject(button);

        cout << "You unscrew the control panel and expose a small red button inside.\n";
    }
    else {
        cout << "You can't use the screwdriver on that.\n";
    }


}


/* void Game::useKeycard(Object* door)
* 
* 
* ===============****=======================
* 
* 
Handles using the screwdriver on different objects.
- Checks if the target object exists; if not, notifies the player.
- If used on the "vent":
  Opens it if locked and marks it as a safe zone for hiding.
  If already open, informs the player.
- If used on the "control panel":
  Opens it only once by checking controlPanelUnscrewed.
  Reveals a new "button" object inside the panel and adds it to the room.
- If used on anything else, informs the player that it’s not a valid use.
*/



void Game::useKeycard(Object* door) {
    if (door->getName() == "pod door") {
        cout << "You cannot open that door with a keycard" << endl;
        return;
    }
    else if (!door) {                                      
        cout << "There is no such door here.\n";
        return;  // stops the function if door is not found
    }
    // Prevent unlocking passcode doors with the keycard
    else if (door->getIsPasscodeLocked()) {
        cout << "The keycard doesn’t work on this type of door. It requires a passcode.\n";
        return;
    }

    if (playerIsHidden) {
        playerIsHidden = false; 
        cout << "You step out from your hiding spot.\n";
    }

    if (door->getIsLocked()) {
        door->setIsLocked(false); 
        cout << "You swipe the keycard, and the door unlocks with a loud beep.\n";
      
    }
    else {
        cout << "The door is already unlocked.\n";
    }
}

// New method to check if the current room has the passcodedoor.

void Game::typeCode(int enteredCode)
{
    // check current room for passcode door
    Object* door = currentRoom->getObject("passcode door");
    if (!door)
    {   
        // if there are no such doors inform the player.
        cout << "There is no keypad door here.\n";
        return;
    }
    // Check if the player has discovered both halves of the passcode
    if (!foundcode1 ||!foundcode2) {
        cout << "You cannot enter a passcode until you have discovered both halves.\n";
        return;
    }
    // Compare the entered code with the actual stored passcode

    if (enteredCode == passcode) {
        cout << "The keypad flashes green. The door unlocks.\n";
        door->setIsLocked(false);
    }
    else {
        cout << "Incorrect code. Try again.\n";
        alien.setCurrentRoom(currentRoom);
        cout << "A distant screech echoes… Something has been alerted.\n";
    }
}


void Game::goDoor(const string& doorName) { // New method to go through a door
	Object* door = currentRoom->getObject(doorName); //check if the door exists in the current room
	if (!door) {
		cout << "There is no " << doorName << " here.\n";
		return;
	}
    if (door->isTakeable()) { //stop player trying to open or go a keycard
        cout << "You can not open this or go through it. \n";
        return;
    }

    // check for passcode locked door
    if (door->getIsPasscodeLocked()) {
        if (door->getIsLocked()) {
            std::cout << "The door is locked. You must enter the passcode.\n";
            return;
        }
    }
    // Special condition for the escape pod door
    if (door->getName() == "escape pod door") {
        if (!(firstButtonPressed && darkRoomButtonPressed)) {
            cout << "The escape pod door is sealed tight. It seems two systems must be activated first.\n";
            return;
        }
    }
    // for usual keycard doors
    else if (door->getIsLocked()) {
        cout << "The door is locked.\n";
        return;
    }
    

     Room* nextRoom = currentRoom->getNeighbour(doorName); // get the neighbouring room through the door
     if (nextRoom) {
         if (playerIsHidden) {
			 playerIsHidden = false; // unhide player when they go through a door
			 cout << "You step out from your hiding spot.\n";
         }
         cout << "You go through the " << doorName << " and enter the next room.\n";
         setCurrentRoom(nextRoom); // move to the neighbouring room
         cout << currentRoom->getDescription() << endl;

         // IF captain is following and is alive cout the folllowng
         if (captain.getIsFollowing() && captain.getIsAlive()) {
             cout << "Captain Emaruv Santron steps in behind you, scanning the corners of the room.\n";
         }

         door->setIsLocked(true); // lock the door again after going through
         if ((door->getName()) == "bathroom door" || door->getName() == "worker door") { //don't lock player in bathroom or worker room 
                door->setIsLocked(false);
            
         }
                 
     }
     else {
         cout << "There is no room connected to this door.\n";
     }
}

void Game::hide(string noun) {
    Object* hideSpot = currentRoom->getObject(noun);
    if (hideSpot && hideSpot->getIsSafeZone()) {
        playerIsHidden = true;
        cout << "You hide inside the " << noun << ". Stay quiet...\n";
        if (noteCounter == 4) {
            currentRoom->addObject(alienNote);
        }
    }
    else {
        cout << "You can not hide there.\n";
    }
}

void Game::unhide() {
	if (playerIsHidden) {
		playerIsHidden = false;
		cout << "You step out from your hiding spot.\n";
	}
	else {
		cout << "You are not hiding.\n";
	}
}

void Game::setIsHidden(bool hidden) {
	playerIsHidden = hidden;
}

bool Game::getIsHidden() {
	return playerIsHidden;
}

/*Function to combine two objects so one of the objects will start working*/
bool Game::combine(Object* batt, Object* flash) {
    if (flash->getIsWorking()) {
        cout << "You already have a working flashlight." << endl;
        return false;
    }
    bool hasBatt = inventory.gotObject(batt->getName());
    bool hasFlash = inventory.gotObject(flash->getName());
    if (!hasBatt && !hasFlash) {
        cout << "You do not have the flashlight and the batteries." << endl;
        return false;
    }
    if (!hasBatt) {
        cout << "You do not have batteries." << endl;
        return false;
    }
    if (!hasFlash) {
        cout << "You don not have the flashlight." << endl;
        return false;
    }

    // Combine them
    inventory.deleteObject(batt);        // remove the batteries
    flash->setWorking(true);             // mark flashlight as working
    flash->setDescription("Working flashlight");
    cout << "You combined the batteries with the flashlight." << endl;
    return true;
}

/*======================================================================================================================================
* ======================================================================================================================================
* FUNCTIONS FOR NOTES 
* ========================================================================================================================================
==========================================================================================================================================*/

/*================================================================= 
UseMirror FUNCTION TO REVEAL THE TEXT IN THE NOTE FROM THE BATHROOM 
===================================================================*/
bool Game::useMirror(Object* n) {
    if (currentRoom->getName() != "Bathroom") {
        cout << endl << "There is no mirror here" << endl;
        return false;
    }
    if(!inventory.gotObject("note-2")) {
        cout << endl << "What are you doing?" << endl;
        return false;
    }
    if (!bathroomNote->getNoteText().empty()) {
        cout << "You have already revealed the text" << endl;
        return true;
    }
    bathroomNote->setNoteText(mirrorText);
    cout << "You are using mirror to reflect the text in the note....\n Now you can read it" << endl;
    increaseNoteCounter(bathroomNote);
    return true;
}

/*
*  IF STATEMENTS SO THE USER IS ABLE TO TAKE NOTES WITHOUT SPECIFYING THE NUMBER OF THE NOTE
*/

string Game::takeNoteRoom(string noun) {
    if (currentRoom->getId() == "bathroom")
        return noun = "note-2";
    else if (currentRoom->getId() == "storageArea")
        return noun = "note-1";
    else if (currentRoom->getId() == "darkRoom")
        return noun = "note-3";
    else if (currentRoom->getObject("note-5") == alienNote)
        return noun = "note-5";
    else {
        cout << "There is no paper" << endl;
        return noun = "";
    }
}

void Game::lightRevealing() {
    if (!inventory.gotObject("flashlight")) {
        cout << "You do not have a flashlight.\n";
        return;
    }

    if (!inventory.gotObject("note-3")) {
        cout << "What are you trying to do?\n";
        return;
    }
    switch (flashlightCounter) {
    case 0:
        cout << "You shine the flashlight on the note.\n"
            << "Something faint flickers... too blurry to read.\n";
        darkText =
            "INCIDENT REPORT - SUBJECT: (not readable)";
        darkNote->setNoteText(darkText);
        break;

    case 1:
        cout << "You shine again. More of the writing appears.\n";
        darkText =
            "INCIDENT REPORT - SUBJECT: (*heavily redacted*)\n"
            "Date: 3 days prior...\n"
            "Exposure to experimental (*not readable*)...";
        darkNote->setNoteText(darkText);
        break;

    case 2:
        cout << "You focus the flashlight one last time.\nThe full message reveals itself.\n";
        darkText =
            "INCIDENT REPORT - SUBJECT: (*heavily redacted*)\n"
            "Date: 3 days prior to current date\n"
            "Location: Research Lab (Dark Room)\n"
            "\n"
            "Exposure to experimental compound - molecular changes detected.\n"
            "Subject volatile. Memory degradation observed.\n"
            "\n"
            "Possible reversal protocol exists but untested.\n"
            "Required components located in:\n"
            "\n"
            "CryoStart medical (*smudged*)\n"
            "Worker's Room secured (*not readable*)\n"
            "\n"
            "Transformation may be reversible if original (torn) recovered.\n"
            "Subject dangerous but showed moments of clarity.\n"
            "\n"
            "Do not terminate on sight.\n"
            "\n"
            "Dr. Marcus Webb, Medical Officer";
        darkNote->setNoteText(darkText);
        increaseNoteCounter(darkNote);
        break;

    default:
        cout << "You already revealed all the text.\n";
        return;
    }

    flashlightCounter++;
}


void Game::createBathroomNote() {
    if (currentRoom->getName() != "Bathroom") {
        cout << "There is no mirror here\n";
        return;
    }
    cout << "You are looking at yourself......\n"
        "You look tired.......\n"
        "You need to take a rest.......\n\n";
    if (inventory.gotObject("note-2")) {
        return;
    }
    if (currentRoom->getObject("note-2") != bathroomNote) {
        currentRoom->addObject(bathroomNote);
    }
    cout << "You notice a piece of paper stuck in the right corner of the mirror.\n";
}


void Game::increaseNoteCounter(Object* obj) {
    if (!obj->getNoteText().empty()) {
        noteCounter++;
        cout << endl << noteCounter << endl;
    }
}

bool Game::isNote(string obj) {
    return obj == "note" || obj == "note-2" || obj == "paper" || obj == "note-3";
}

bool Game::isMirror(string obj) {
    return obj == "mirror";
}

bool Game::isFlashlight(string obj) {
    return obj == "flashlight";
}
void Game::createDarkNote() {
    if (currentRoom->getId() != "darkRoom") {
        cout << "There are no papers here.\n";
        return;
    }

    // Must have working flashlight
    if (!flashlight->getIsWorking()) {
        cout << "It is too dark to see anything.\n";
        return;
    }

    // Description of the papers
    cout << "You kneel down and sort through the scattered papers.\n"
        "Most are torn or unreadable—but one looks intact...\n";

    if (currentRoom->getObject("note-3") != darkNote) {
        currentRoom->addObject(darkNote);
    }

}

void Game::process()
{
    string input, noun, whatToUseOn;
    Actions action;
    

    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, input)) break; // handle EOF cleanly

        //Ignore empty input (ENTER alone)
        if (input.size() == 0) {
            continue;
        }

        if (!parser.parse(input, action, noun, whatToUseOn)) { 

            if (inEscapeSequence) { //note, needs to reset properly
                cout << "You hesitate... the alien catches you.\n"; //this is to prevent player surviving if they enter nonsense
                bool survived = alien.killPlayer(&captain);
                if (survived) {
                    cout << "You must keep running\n";
                    continue;
                }
                // tryna fix bugs
               // inEscapeSequence = false;
              //  runCount = 0;
              //  alien.killPlayer(& captain);
              //  continue;
            }

            cout << "Invalid command. Type 'help' for a list of commands.\n";
            continue;
        }

        if (inEscapeSequence && action != Actions::RUN) { //note, needs to reset properly
            cout << "You hesitate... the alien catches you.\n";
            bool survived = alien.killPlayer(&captain);
            if (survived) {
                cout << "You must keep running\n";
                continue;
            }
           // inEscapeSequence = false; 
           // runCount = 0;
  
           // alien.killPlayer(& captain);
           // continue;
            return;
        }

        switch (action) {

        case Actions::HELP:
            getHelp();
            break;

        case Actions::LOOK:
            if (noun == "around" || noun == "room") {
                //check if the player is in the darkRoom and has the lighter that does not work
                if (currentRoom->getId() == "darkRoom" && flashlight->getIsWorking() == false) {
                    cout << "It is too dark to see anything. Maybe you need a working flashlight.\n";
                    break; // stop further look processing
                }
                if (currentRoom->getId() == "darkRoom" && flashlight->getIsWorking()) {
                    currentRoom->setDescription("The room is dark and quiet, with only a faint light seeping through a crack in the door.\nScattered across the floor, a mess of papers lies in disordered piles, as if someone left in a hurry.\n");
                }
                if (currentRoom) {
                    cout << currentRoom->getDescription() << endl;
                    cout << "Objects in room:" << endl;
                    currentRoom->printAllObjects();
                    cout << endl;
                    //show captain if following and alive
                    if (captain.getIsFollowing() && captain.getIsAlive()) {
                        cout << "Captain Santron stands nearby, watching the shadows.\n";
                    }

                }
                if (currentRoom->getName() == "CryoStart") {
                    if (controlPanelUnscrewed && !firstButtonPressed)
                        cout << "The control panel is open. A small red button glows faintly inside.\n";
                    else if (controlPanelUnscrewed && firstButtonPressed)
                        cout << "The control panel is open, but the button has already been pressed.\n";
                }

                if (currentRoom->getName() == "bathroom") {              // Find the stall object in the current room
                    Object* stall = currentRoom->getObject("stall");     // Make sure the stall exists AND is open
                    if (stall && stall->getIsOpen()) {
                        cout << "Inside the stall, you notice something scratched into the wall: '--"
                            << passcode2 << "'\n";                      // show the second half of the passcode
                    }
                }
            }
            else if (noun == "stall") {
                Object* stall = currentRoom->getObject("stall");        // find the stall object in the room
                if (stall) {
                    if (stall->getIsOpen()) {
                        cout << "Inside the stall, you see part of a passcode: '--"  // if the stall is open show the passcode
                            << passcode2 << "'\n";
                    }
                    else {
                        cout << "It is a closed stall.\n";                  // if its not open yet, show there's no stall here
                    }
                }
                else {
                    cout << "There is no stall here.\n";
                }
            }
            else if (noun == "book") {                                  // handle look book
                if (inventory.gotObject("book")) {                      // checks if the player has the book already. If found then checks and discovers the first half of the code
                    foundcode1 = true;
                    cout << "You flip through the book and find half a passcode: '" << passcode1 << "--'.\n";
                }
                else {
                    cout << "There is nothing to see.\n";
                }
            }
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            else if (noun.empty()) {
                cout << "Look at what?\n";
            }

            /* 
            ================================
             FOR MIRROR IN THE BATHROOM ROOM
            ================================
            */

            else if (noun == "mirror") {
                createBathroomNote();
            }

            else if (noun == "paper" || noun == "papers") {
                createDarkNote();
            }

            /*
            If none of the special 'look' cases matched (like book or stall),
            this block handles generic "look <object>" commands.
            if the object exists in the current room, print its description.
            If the object is not in the room, check if it's in the player's inventory

            */
            else {
                Object* obj = currentRoom->getObject(noun);
                if (obj) {
                    cout << obj->getDescription() << endl;
                }
                else if (inventory.gotObject(noun)) {
                    Object* invobj = inventory.getObject(noun);
                    if (invobj) cout << invobj->getDescription() << endl;  // If the object exists in inventory, show its description
                    else cout << "You examine the keycard.\n";
                }
                else {
                    cout << "You do not have the " << noun << ".\n";
                }
            }
            break;


        case Actions::TAKE:
            if (noun.empty()) {
                cout << "Take what?\n";
                break;
            }

            if (!currentRoom) {
                cout << "There is nowhere to take that from.\n"; // if player somehow not in room
                break;
            }

            {
                if (currentRoom->getId() == "bathroom" && noun == "mirror") {
                    cout << "It seems that the mirror is fixed on the wall, I do not think I can take that" << endl;
                    break;
                }
                //=====================================================================================================================
                if (isNote(noun)) {
                    noun = takeNoteRoom(noun);
                }
                Object* obj = currentRoom->getObject(noun);

                // Take control panel doesnt show the right output so i have m
                if (!obj) {
                    if (noun == "control" || noun == "panel")
                        obj = currentRoom->getObject("control panel");
                }
                if (!obj) {
                    cout << "There is no " << noun << " here.\n";
                    break;
                }
                if (!obj->isTakeable()) {
                    cout << "You can't take the " << noun << ". It seems fixed in place.\n"; // object not takeable
                    break;
                }


                inventory.addObject(obj); // add to inventory, remove from room, tell player
                currentRoom->removeObject(noun);
                cout << "You picked up the " << noun << ".\n";


                /*========================================================================================
                =======================================================================================
                ======================================================================================*/

                increaseNoteCounter(obj);

                //ONLY TO CHECK IF THE COUNTER IS WORKING. WILL BE DELETED AFTER FINISHING
                cout << endl << noteCounter << endl << endl;
            }
            break;

        case Actions::INVENTORY:
            inventory.showInventory();
            break;

        case Actions::MAP:
            displayMap();
            break;

        case Actions::USE:
        {
            if (noun.empty()) {
                cout << "Use what?\n";
                break;
            }
            // Control panel usage
            if (noun == "control" || noun == "panel") {
                Object* panel = currentRoom->getObject("control panel");
                if (!panel) {
                    cout << "There is no control panel here.\n";
                    break;
                }
                // If unlocked & unscrewed 
                if (controlPanelUnscrewed) {
                    cout << "The control panel is unlocked and ready to use.\n";
                    break;
                }
                //check if set to locked
                if (panel->getIsLocked()) {
                    cout << "The control panel is screwed shut. Maybe you need a screwdriver to open it.\n";
                    break;
                }
            }

            //Combining batteries and flashlight
            if (noun == "flashlight") {
                if (whatToUseOn == "batteries") {
                    combine(batteries, flashlight);
                    break;
                }
            }
            else if (noun == "batteries") {
                if (whatToUseOn == "flashlight") {
                    combine(batteries, flashlight);
                    break;
                }
            }

            // Keycard usage
            //check if keycard
            if (noun == "keycard") {
                if (!inventory.gotObject("keycard")) {
                    cout << "You do not have a keycard to use.\n";
                    break;
                }

                if (whatToUseOn.empty()) {
                    cout << "Use on what?\n";
                    break;
                }
                // if the keycard exists in the current room

                Object* obj = currentRoom->getObject(whatToUseOn);
                if (!obj) {
                    cout << "There is no " << whatToUseOn << " here to use the keycard on.\n";
                    break;
                }
                // Only allow keycards on objects that are locked and not takeable (doors)
                if (!obj->isTakeable() && obj->getIsLocked() && obj->getName() != "control panel") {
                    useKeycard(obj);
                }
                else {
                    cout << "The keycard won't work on that.\n";
                }
                break;

            }

            // Screwdriver usage
            //check if screwdriver
            if (noun == "screwdriver") {
                if (!inventory.gotObject("screwdriver")) {
                    cout << "You do not have a screwdriver.\n";
                    break;
                }

                if (whatToUseOn.empty()) {
                    cout << "Use on what?\n";
                    break;
                }
                // if the keycard exists in the current room
                Object* obj = currentRoom->getObject(whatToUseOn);
                if (!obj) {
                    cout << "There is no " << whatToUseOn << " here to use the screwdriver on.\n";
                    break;
                }

                useScrewdriver(obj); // handles vent, control panel, etc.
                break;
            }
            if (noun == "button") {
                Object* button = currentRoom->getObject("button");
                pressButton(button);
                break;
            }

            //============================ USE MIRROR ON NOTE ============================

            if ((isMirror(noun) && isNote(whatToUseOn)) || (isNote(noun) && isMirror(whatToUseOn))) {
                useMirror(bathroomNote);
                break;
            }

            //=======================================================USAGE FLASHLIGHT ON THE NOTE=====================================
            if ((isFlashlight(noun) && isNote(whatToUseOn)) || (isNote(noun) && isFlashlight(whatToUseOn))) {
                lightRevealing();
                break;
            }

            // Fallback for other items that arent applicable in use case scenario(e.g, door)
            cout << "You can't use that right now.\n";
            break;
        }

        case Actions::PRESS:
        {
            if (noun.empty()) {
                cout << "Press what?\n";
                break;
            }

            Object* button = currentRoom->getObject(noun);
            if (!button) {
                cout << "There is nothing like that to press here.\n";
                break;
            }

            pressButton(button);
            break;
        }

        case Actions::WAKE:
        {
            if (noun.empty()) {
                cout << "Wake who?\n";
                break;
            }

            if (currentRoom->getId() != "captainRoom") {
                cout << "There is no one here to wake.\n";
                break;
            }

            if (noun != "captain") {
                cout << "That doesn't seem to respond.\n";
                break;
            }

            if (captain.getIsAwake()) {
                cout << "The captain is already awake.\n";
                break;
            }

            captain.setIsAwake(true);
            cout << "You wipe frost from the cryo pod's glass and find an older man inside.\n";
            cout << "You fumble with the manual release until the lid hisses open.\n";

            cout << " \n";

            coolTyping ("His eyes flutter, and he whispers, \"Wata... watah...\"\n");
            cout << "Type: serve water to captain\n";
            break;
        }
        case Actions::SERVE:
        {
            if (noun.empty()) {
                cout << "Serve what?\n";
                break;
            }

            if (noun != "water") {
                cout << "You can't serve that right now.\n";
                break;
            }

            if (whatToUseOn.empty() || whatToUseOn != "captain") {
                cout << "Serve water to whom?\n";
                break;
            }

            if (currentRoom->getId() != "captainRoom") {
                cout << "The captain isn't here.\n";
                break;
            }

            if (!captain.getIsAwake()) {
                cout << "No one here seems awake enough to drink.\n";
                break;
            }

            if (captain.getHasWater()) {
                cout << "The captain has already had water.\n";
                break;
            }

            // Conversation sequence
            captain.setHasWater(true);

            coolTyping  ("You find a bottle of water on a nearby shelf and bring it to the captain.\n");
            coolTyping  ("He drinks greedily, some color returning to his face.\n\n");

            cout << "Captain: \"Gh... thank you. It looks like u got yourself into some trouble..like i did....UMMM... what year is it?\"\n";

            int year = 0;
            while (true) {
                cout << "> ";
                string yearInput;
                if (!getline(cin, yearInput)) {
                    cout << "Input closed. Exiting game...\n";
                    exit(0);
                }
                if (yearInput.size() == 0) {
                    cout << "Please enter the year as numbers.\n";
                    continue;
                }
                try {
                    year = stoi(yearInput);

                    // only allow valid input
                    if (year < 1000 || year > 9999) {
                        cout << "Please enter a valid four–digit year (2000–2500).\n";
                        continue;
                    }

                    // pastYear is not negative
                    if (year - 275 < 0) {
                        cout << "That doesn't seem like a real year... try again.\n";
                        continue;
                    }

                    break; //
                }
                catch (...) {
                    cout << "Please enter the year as numbers (for example: 2025).\n";
                }

            }

            int pastYear = year - 275;
            cout <<"Captain: \"By the stars... that means the last time I was awake, it was around " << pastYear << ".\"\n";
            coolTyping  ("Captain: \"Two hundred and seventy-five years... gone in a blink.\"\n\n");

            cout << "Press ENTER to listen to the captain's story...\n";

            // prompting the player to press enter but this would take anything as legal input
            string dummy;
            getline(cin, dummy);

            coolTyping  ("\He says: My name is Emaruv Santron.\n");

            coolTyping  ("\Then he leans back against the pod frame, staring past the ceiling.\n");
            coolTyping  ("\"Back then, this station was a frontier outpost,\" he begins.\n");
            coolTyping  ("\"We ferried colonists, cargo, and an egg we never should've taken aboard.\"\n");
            coolTyping  ("\"When things went bad, I locked myself in cryo, hoping someone in the future would clean up the mess.\"\n");
            coolTyping  ("\"Looks like that job landed on you.\"\n\n");

            coolTyping  ("Captain: \"Enough about me. What's your name, kid?\"\n");
            cout << "> My name is : ";
            string name;
            if (!getline(cin, name)) {
                cout << "Input closed. Exiting game...\n";
                exit(0);
            }
            if (name.empty()) {
                name = "kid";
            }

            captain.setPlayerName(name);
            captain.setIntroduced(true);
            captain.setIsFollowing(true);

            coolTyping("Captain: \"All right, "); cout << name << ".\"\n";
            coolTyping("\"Stay close. I'll watch your back as long as I can.\"\n");

            break;
        }


        case Actions::RUN:
            if (inEscapeSequence) {
                runCount++; //increase run count so after they pass 4 it ends
                    switch (runCount) {
                    case (1):
                        cout << "The alien is right behind you, type RUN, one of these escape pods has got to work!" << endl;
                        break;
                    case (2):
                        cout << "Fierce sounds are coming from you. Type RUN, you need to keep going!" << endl;
                        break;
                    case (3):
                        cout << "You see something in the distance, a working escape pod! Type RUN, keep going!" << endl;
                        break;
                    case (4):
                        cout << "You are almost at the working escape pod! Type RUN and keep going!" << endl;
                        break;
                    default:
                        cout << "You see one last working escape pod." << endl;

                        // if the captain and the player made it out. 
                        if (captain.getIsFollowing() && captain.getIsAlive()) {
                            string nm = captain.getPlayerName();
                            if (nm.empty()) nm = "kid";
                            coolTyping ("Captain Santron slumps into the seat beside you and lets out a tired laugh.\n");
                            coolTyping ("\"We made it out, "); cout << nm << ". Somehow.\"\n";
                        }
                        // if only the player has made it out
                        else if (captain.getHasProtectedOnce() && !captain.getIsAlive()) {
                            coolTyping ("As the pod drifts into the void, you remember Captain Santron's last stand.\n");
                            coolTyping("His sacrifice bought you this one chance at survival.\n");
                        }

                        coolTyping("With a push of a button, your escape pod shoots off back to the nearest safe colony between you and your destination.\n");
                        cout << "You win!" << endl;
                        exit(0);
                    }
                     if (noun.empty()) { //prevents run stil asking where this might be redundant
                break;
            }
                     else if (inEscapeSequence) {
                         break;
                     }
            }
        case Actions::GO:
        case Actions::OPEN:
            if (noun.empty()) {
                cout << "Where?\n";
                break;
            }

            // CONTROL PANEL
            if (noun == "control panel") {
                Object* panel = currentRoom->getObject("control panel");
                if (!panel) {
                    cout << "There’s no control panel here.\n";
                    break;
                }
                if (controlPanelUnscrewed) {
                    cout << "The control panel is already open, revealing a red button inside.\n";
                }
                else if (panel->getIsLocked()) {
                    cout << "The control panel is screwed shut. Maybe you need a screwdriver to open it.\n";
                }
                else {
                    // Player opens/unscrews it
                    controlPanelUnscrewed = true;
                    cout << "You unscrew the control panel and expose a small red button inside.\n";
                }
                break;
            }

            // VENT
            if (noun == "vent") {
                Object* vent = currentRoom->getObject("vent");
                if (!vent) {
                    cout << "There is no vent here.\n";
                    break;
                }

                if (vent->getIsLocked()) {
                    cout << "The vent is locked. Maybe you need a tool to open it.\n";
                }
                else {
                    cout << "The vent is open now.\n";
                }
                break;
            }

            // STALL
            if (noun == "stall") {
                Object* stall = currentRoom->getObject("stall");
                if (!stall) {
                    cout << "There's no stall here.\n";
                    break;
                }

                if (!stall->getIsOpen()) {
                    stall->setIsOpen(true);
                    foundcode2 = true;
                    cout << "You open the stall. Maybe there is something inside? Maybe I should take a closer look?\n";
                }
                else {
                    cout << "The stall is already open. Maybe there is something inside? Maybe I should take a closer look?\n";
                }
                break;
            }

            // BUTTON
            if (noun == "button") {
                cout << "You can not open a button.\n";
                break;
            }

            // DEFAULT: treat as door
            goDoor(noun);
            break;

        case Actions::PEEK://if they entered a door name peek otherwise not allowed
            if (noun.empty()) {
                cout << "Peek through what? \n";
                break;
            }
            else {
                peekDoor(noun);
            }
            break;

        case Actions::TYPE:
            if (noun.empty()) {
                cout << "Enter a code.\n";
                break;
            }
            try {
                int entered = std::stoi(noun);
                typeCode(entered);
            }
            catch (...) {
                cout << "Invalid code format.\n";
            }
            break;

        case Actions::HIDE: { // hide in vent or locker
            if (noun.empty()) {
                cout << "Hide where?\n";
                break;
            }

            Object* obj = currentRoom->getObject(noun);
            if (!obj) {
                cout << "That object does not exist.\n";
                break;
            }

            // Only allow hiding in vent or locker
            if (obj->getName() != "vent" && obj->getName() != "locker") {
                cout << "You can not hide there.\n";
                break;
            }

            if (obj->getIsLocked()) {
                cout << "The " << obj->getName() << " is locked. You can not hide in it yet.\n";
                break;
            }

            if (!getIsHidden()) {
                hide(noun);  // call existing hide() function

            }
            else {
                cout << "You are already hidden.\n";
            }
            break;
        }

        case Actions::UNHIDE: { // unhide anywhere
            unhide();
            break;
        }
        case Actions::READ: {
            if (noun.empty()) {
                cout << "Read what?\n";
                break;
            }
            //===============================================================================================================================
            if (noun == "note-2") {
                if (bathroomNote->getNoteText() == "" && inventory.gotObject("note-2")) {
                    cout << endl << "It seems like the text is reversed....\n I cannot read that" << endl;
                    break;
                }
                else {
                    cout << bathroomNote->getNoteText() << endl;
                    break;
                }
                cout << "it did not go to any if statement" << endl;
            }
            else if (noun == "note-1" && inventory.gotObject("note-1")) {
                cout << storageNote->getNoteText() << endl;
                break;
            }
            else if (noun == "note-5" && inventory.gotObject("note-5")) {
                cout << alienNote->getNoteText() << endl;
                break;
            }
            else if (noun == "note-3" && inventory.gotObject("note-3")) {
                if (flashlightCounter == 0) {
                    cout << "Note is empty" << endl;
                    break;
                }
                else {
                    cout << darkNote->getNoteText() << endl;
                    break;
                }
            }
            else {
                cout << "you do not have this to read" << endl;
                break;
            }
        }
        default:
            cout << "You can not do that right now.\n";
            break;
        }

        alien.increaseTurnCounter(currentRoom, playerIsHidden, & captain);
        }
    }



////////////////////////////////