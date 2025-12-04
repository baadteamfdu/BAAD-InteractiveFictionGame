#include "Game.h"
#include "Room.h"
#include "Object.h"
#include "Inventory.h"
#include "Parser.h"   // make sure this exists; otherwise comment this and use the fallback enum below
#include "Alien.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// If your Actions enum lives elsewhere, include it there.
// If not, uncomment this fallback:
// enum class Actions { HELP, LOOK, TAKE, INVENTORY };

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
        "A large bay leading to the final escape pod door.The control panel beside it is screwed shut.\n"
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
        "The room is dark and quiet, with only a faint light seeping through a crack in the door.\n"
    );

    setCurrentRoom(cryoStart);

    // Add objects to starting room

    //NOTE ALL OBJECTS MUST HAVE LOWERCASE NAMES AT LEAST FOR NOW, AS TOLOWER IS IN PARSER
    // Add objects to starting room
    Object* keycard = new Object("keycard", "A Level A access card with a magnetic stripe.", true);
    cryoStart->addObject(keycard);

    // Book in worker's room
    Object* book = new Object("book", "An old logbook", true); // creating a book object
    workersRoom->addObject(book); //placing that book in the workers woom. Offcourse is takeable

    //Screwdriver in storage area
    Object* screwdriver = new Object("screwdriver", "A small screwdriver. Could be handy.", true);
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

    //code halves inside objects 
  //  Object* codePart1 = new Object("code part 1", "Half of the passcode: '--" + to_string(passcode % 100) + "'", true);
  //  Object* codePart2 = new Object("code part 2", "Half of the passcode: '" + to_string(passcode / 100) + "--'", true);
  //  stall->addContainedObject(codePart1);
  //  book->addContainedObject(codePart2);

    // Creating doors
    Object* cryoDoor = new Object("cryo door", "A door with a card reader", false, true); //cryo card door
    // passcode door
    Object* passcodeDoor = new Object("passcode door", "A door with a keypad lock", false, true); // added the passcode door object.
    passcodeDoor->setIsPasscodeLocked(true); // door is locked
    passcodeDoor->setPasscode(passcode);

    Object* dockDoor = new Object("dock door", "A door to the Dock Room", false, false);
    Object* escPodChamDoor = new Object("escape pod door", "A door to the Escape Pod Door", false, false);
    Object* finalRoomDoor = new Object("pod door", "A door to the Final Room", false, true);
    Object* workersDoor = new Object("worker door", "A door to the Worker’s Room", false, false); //this is not hardcoded and the player will lock it behind them.
    Object* bathroomDoor = new Object("bathroom door", "A door to the Bathroom", false, false);
    Object* cafeteriaDoor = new Object("cafeteria door", "A door to the Cafeteria", false, false);
    Object* kitchenDoor = new Object("kitchen door", "A door to the Kitchen", false, false);
    Object* darkDoor = new Object("dark door", "A door to the Dark Room", false, false);

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

    allRooms = { cryoStart, cryoHall, storageArea, dock, escapePodChamber, finalRoom, workersRoom, bathroom, cafeteria, kitchen, darkRoom };
    cryoHall->setPosition(2, 2);           // center
    storageArea->setPosition(1, 2);
    dock->setPosition(0, 2);
    escapePodChamber->setPosition(0, 3);
    finalRoom->setPosition(0, 4);

    workersRoom->setPosition(3, 2);
    bathroom->setPosition(3, 3);
    cafeteria->setPosition(2, 3);
    darkRoom->setPosition(2, 4);
    kitchen->setPosition(1, 3);
    cryoStart->setPosition(3, 1);
    // Hiding Object
	Object* safeZone = new Object("locker", "A metal locker large enough to hide inside", false, false, true); // creating a locker object as a safe zone

	workersRoom->addObject(safeZone); // placing the locker in the worker's room
    //let Alien Access rooms
    alien.addAllRooms(allRooms);
    }

Room* Game::getCurrentRoom() {
    return currentRoom;
}

void Game::setCurrentRoom(Room* nextRoom) {
    currentRoom = nextRoom;
    //activates alien once player enters cryohall for the first time, I don't know a better way
    if (currentRoom->getId() == "cryoHall" && (alien.getIsActive() == false)) {
        alien.setActive(true);
        alien.move();
        cout << "You see a passcode door on one side, and an ajar, unlocked keycard door on the other." << endl; //hint to tell player to hide and they don't need to use keycard
    }
    if (currentRoom->getId() == "finalRoom") { //added winning for the deliverable
        cout << "You see one last working escape pod." << endl; 
        cout << "With a push of a button, your escape pod shoots off back to the nearest safe colony between you and your destination." << endl;
        cout << "You win!" << endl;
        exit(0);
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
	cout << "hide <object name>\n";
	cout << "unhide\n";
    cout << "reset\n";
    cout << "quit\n";
    cout << "help\n";


}
//this function makes it so that the whole game get restarted
void Game::resetGame()
{
    destroyWorld();
    generatePasscode();
    init();

    cout << "Game restarting..." << endl;
}
//if the player gives up this function makes it so that you can quit the game
void Game::quitGame()
{
    destroyWorld();
    cout << "Game over!" << endl;
    exit(0);
}
void Game::handlePlayerDeath()
{
    cout << "\nThe alien catches you. You feel its claws close around you.\n";
    cout << "Your vision fades as everything goes quiet.\n\n";

    while (true)
    {
        cout << "Type 'reset' to restart or 'quit' to exit: ";

        string choice;
        if (!getline(cin, choice))
        {
            // If input somehow fails, just quit cleanly.
            quitGame();
            return;
        }

        // Make input lowercase so RESET, Reset, etc. still work.
        for (char& c : choice)
        {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (choice == "reset")
        {
            cout << "\nRestarting from the beginning...\n\n";
            resetGame();
            return; // back to the main game loop with a fresh world
        }
        else if (choice == "quit")
        {
            quitGame(); // this will also exit(0)
            return;
        }
        else
        {
            cout << "Please type exactly 'reset' or 'quit'.\n";
        }
    }
}

void Game::destroyWorld()
{
    alien.clearRooms();
    alien.setActive(false);

    // Clear the non-door objects and delete the Rooms themselves
    for (auto* room : allRooms)
    {
        room->removeAllObjects(); // Clears all roomObjects, but only deletes the UN-SHARED ones (as per the fix above)
        delete room;
    }

    // Delete the shared door objects once
    for (auto* door : allDoors)
    {
        delete door;
    }

    //clears inventory and rooms
    allRooms.clear();
    //Clear the vector of door pointersese
    allDoors.clear(); 
    inventory.clear();

    //player is not in the current room anymore
    currentRoom = nullptr;

    // ...
}

//this makes a new random passcode so that the game isn't beatable consistently
void Game::generatePasscode()
{
    passcode = rand() % 9000 + 1000;
    passcode1 = passcode / 100; //first two digits of passcode being randomized
    passcode2 = passcode % 100; //last two digits of passcode being randomized
    //this makes sure that the player starts off with new code
    foundcode1 = false;
    foundcode2 = false;
}

//this functions displays the map that is used for the game.
//
void Game::displayMap() const
{
    // If no rooms exist (e.g., the game world hasn’t been built), abort early.
    if (allRooms.empty())
    {
        cout << "No map available.\n";
        return;
    }

    // Instead of cutting off names, we calculate the width dynamically
    // based on the longest room name so that all labels fit nicely.
    int maxNameLen = 0;
    for (Room* r : allRooms)
    {
        if (!r) continue;
        int len = (int)r->getName().size();
        if (r == currentRoom) len += 1; // for the '*'
        if (len > maxNameLen) maxNameLen = len;
    }

    // Add 2 for the [ ] around the name
    int CELL_WIDTH = maxNameLen + 2;

    // Clamp to a reasonable range so it’s not insanely wide or tiny
    if (CELL_WIDTH < 12) CELL_WIDTH = 12;
    if (CELL_WIDTH > 26) CELL_WIDTH = 26;

    // Make a label for each room
    auto labelFor = [&](Room* r)
        {
            string base = (r == currentRoom ? "*" : "") + r->getName();

            // Only crop if the name is REALLY longer than our max width
            if ((int)base.size() > CELL_WIDTH - 2)
                base = base.substr(0, CELL_WIDTH - 2);

            string label = "[" + base + "]";
            if ((int)label.size() < CELL_WIDTH)
                label.append(CELL_WIDTH - label.size(), ' ');

            return label;
        };

    // Find coordinate bounds
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

    int rows = maxY - minY + 1;
    int cols = maxX - minX + 1;

    // Build grid of empty cells
    vector<vector<string>> grid(rows, vector<string>(cols, string(CELL_WIDTH, ' ')));

    // Drop each room label in the right grid spot
    for (Room* r : allRooms)
    {
        if (!r) continue;
        int gx = r->getX() - minX;
        int gy = r->getY() - minY;
        if (gx < 0 || gx >= cols || gy < 0 || gy >= rows) continue;

        grid[gy][gx] = labelFor(r);
    }

    // Print it, top row first
    cout << "\n--- MAP ---\n\n";
    for (int y = rows - 1; y >= 0; --y)
    {
        for (int x = 0; x < cols; ++x)
            cout << grid[y][x];
        cout << "\n";
    }

    cout << "\n* = you\n\n";
}


// new function to use a screwdriver on a vent.
void Game::useScrewdriver(Object* vent)
{
    if (!vent)
    {
        cout << "There's nothing like that to use the screwdriver on.\n"; // stops the function if vent is not found
        return;
    }

    // if not a vent 

    if (vent->getName() != "vent")
    {
        cout << "You can't use the screwdriver on that.\n";   
        return;
    }

    // if locked

    if (!vent->getIsLocked())
    {
        cout << "The vent is already open.\n";
        return;
    }

    // updated flags if the player is able to pass through those cases

    vent->setIsLocked(false);
    vent->setIsSafeZone(true);
    cout << "You unscrew the vent cover quietly. You could probably hide inside now.\n";
}

// New method to use a keycard on a door,,; checks if the door exists in the current room
void Game::useKeycard(Object* door) {
    if (!door) {                                      
        cout << "There's no such door here.\n";
        return;  // stops the function if door is not found
    }
    // Prevent unlocking passcode doors with the keycard
    if (door->getIsPasscodeLocked()) {
        cout << "The keycard doesn’t work on this type of door. It requires a passcode.\n";
        return;
    }

    if (playerIsHidden) {
        playerIsHidden = false; // unhide player when they use keycard
        cout << "You step out from your hiding spot.\n";
    }

    // check if the door is locked
    if (door->getIsLocked()) {
        door->setIsLocked(false); // unlock the door
        cout << "You swipe the keycard, and the door unlocks with a loud beep.\n";
      
    }
    // if the door wasnt locked inform the player
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
        cout << "You don't have both halves of the passcode yet.\n";
        return;
    }
    // Compare the entered code with the actual stored passcode

    if (enteredCode == passcode) {
        cout << "The keypad flashes green. The door unlocks.\n";
        door->setIsLocked(false);
    }
    else { cout << "Incorrect code. Try again.\n"; }
}


void Game::goDoor(const string& doorName) { // New method to go through a door
	Object* door = currentRoom->getObject(doorName); //check if the door exists in the current room
	if (!door) {
		cout << "There is no " << doorName << " here.\n";
		return;
	}
    if (door->isTakeable()) { //stop player trying to open or go a keycard
        cout << "You cannot open this or go through it. \n";
        return;
    }

    // check for passcode locked door
    if (door->getIsPasscodeLocked()) {
        if (door->getIsLocked()) {
            std::cout << "The door is locked. You must enter the passcode.\n";
            return;
        }
    }
    // check for usual keycard doors
    if (door->getIsLocked()) {           // Check if this door is a passcode-type door
        cout << "The door is locked.\n"; 
        return;                          // Stop further execution (player can’t go through yet)
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
         door->setIsLocked(true); // lock the door again after going through
         if ((door->getName()) == "bathroom door") { //don't lock player in bathroom 
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
    }
    else {
        cout << "You can't hide there.\n";
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

void Game::process()
{
    string input, noun, whatToUseOn;
    Actions action;

    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, input)) break; // handle EOF cleanly

        if (!parser.parse(input, action, noun, whatToUseOn)) {
            cout << "Invalid command. Type 'help' for a list of commands.\n";
            continue;
        }

        switch (action) {

        case Actions::HELP:
            getHelp();
            break;

        case Actions::LOOK:
            if (noun == "around" || noun == "room") {
                if (currentRoom) {
                    cout << currentRoom->getDescription() << endl;
                    cout << "Objects in room:" << endl;
                    currentRoom->printAllObjects();
                    cout << endl;
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
                        cout << "It's a closed stall.\n";                  // if its not open yet, show there's no stall here
                    }
                }
                else {
                    cout << "There's no stall here.\n";
                }
            }
            else if (noun == "book") {                                  // handle look book
                if (inventory.gotObject("book")) {                      // checks if the player has the book already. If found then checks and discovers the first half of the code
                    foundcode1 = true;
                    cout << "You flip through the book and find half a passcode: '" << passcode1 << "--'.\n";
                }
                else {
                    cout << "There's nothing to see.\n";
                }
            }
            else if (noun == "inventory") {
                inventory.showInventory();
            }
            else if (noun.empty()) {
                cout << "Look at what?\n";
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
                    cout << "You don't have the " << noun << ".\n";
                }
            }
            break;

        case Actions::TAKE:
            if (noun.empty()) {
                cout << "Take what?\n";
                break;
            }

            if (!currentRoom) {
                cout << "There's nowhere to take that from.\n"; // if player somehow not in room
                break;
            }

            {
                Object* obj = currentRoom->getObject(noun); // object not in room
                if (!obj) {
                    cout << "There is no " << noun << " here.\n";
                    break;
                }

                if (!obj->isTakeable()) {
                    cout << "You cannot take this object.\n"; // object not takeable
                    break;
                }

                inventory.addObject(obj); // add to inventory, remove from room, tell player
                currentRoom->removeObject(noun);
                cout << "You picked up the " << noun << ".\n";
            }
            break;

        case Actions::INVENTORY:
            inventory.showInventory();
            break;

        case Actions::MAP:
            displayMap();
            break;

        case Actions::USE:
            if (noun.empty()) {
                cout << "Use what?\n";
                break;
            }

            // Keycard usage
            if (noun == "keycard") {
                if (!inventory.gotObject("keycard")) {
                    cout << "You don't have a keycard to use.\n";
                    break;
                }

                if (whatToUseOn.empty()) {
                    cout << "Use on what?\n";
                    break;
                }

                Object* door = currentRoom->getObject(whatToUseOn);
                if (door) {
                    useKeycard(door);
                }
                else {
                    cout << "There is no door by that name here to use the keycard on.\n";
                }
                break;
            }

            // Screwdriver usage
            if (noun == "screwdriver") {
                if (!inventory.gotObject("screwdriver")) {
                    cout << "You don't have a screwdriver.\n";
                    break;
                }

                if (whatToUseOn.empty()) {
                    cout << "Use on what?\n";
                    break;
                }

                Object* vent = currentRoom->getObject(whatToUseOn);
                if (!vent) {
                    cout << "There is no " << whatToUseOn << " here.\n";
                    break;
                }

                // If the object is a vent, unlock it and mark it as safe
                if (vent->getName() == "vent") {
                    if (!vent->getIsLocked()) {
                        cout << "The vent is already open.\n";
                        break;
                    }
                    useScrewdriver(vent);
                }
                else {
                    cout << "You can't use the screwdriver on that.\n";
                }
                break;
            }

            cout << "You can't use that.\n";
            break;

        case Actions::GO:
        case Actions::OPEN:
            if (noun.empty()) {
                cout << "Where?\n";
                break;
            }

            if (noun == "vent") {
                Object* vent = currentRoom->getObject("vent");
                if (!vent) {
                    cout << "There is no vent here.\n";
                }
                else if (vent->getIsLocked()) {
                    cout << "The vent is locked. Maybe you need a tool to open it.\n";
                }
                else {
                    cout << "The vent is open now.\n";
                }
            }

            else if (noun == "stall") {
            Object* obj = currentRoom->getObject("stall");
                if (obj) {
                    if (!obj->getIsOpen()) {
                        obj->setIsOpen(true);
                        foundcode2 = true;
                        cout << "You open the stall. Maybe there is something inside? Maybe I should take a closer look? \n";
                    }
                    else cout << "The stall is already open. Maybe there is something inside? Maybe I should take a closer look? \n";
                }
                else {
                    cout << "There's no stall here.\n";
                }
            }
            else {
                goDoor(noun);
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
                cout << "That object doesn't exist.\n";
                break;
            }

            // Only allow hiding in vent or locker
            if (obj->getName() != "vent" && obj->getName() != "locker") {
                cout << "You can't hide there.\n";
                break;
            }

            if (obj->getIsLocked()) {
                cout << "The " << obj->getName() << " is locked. You can't hide in it yet.\n";
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

        case Actions::UNHIDE: // unhide anywhere
            unhide();
            break;

        case Actions::QUIT: //gives the player the ability to quit the game
        {
            quitGame();
            break;
        }
        case Actions::RESET: //this restarts the whole game
        {
            resetGame();
            break;
        }

        default:
            cout << "You can't do that right now.\n";
            break;
        }

        alien.increaseTurnCounter(currentRoom, playerIsHidden);
    }
}

