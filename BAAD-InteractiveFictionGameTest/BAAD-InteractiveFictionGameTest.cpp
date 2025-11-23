#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include "../BAAD-InteractiveFictionGame/Object.cpp"
#include "../BAAD-InteractiveFictionGame/Inventory.cpp"
#include "../BAAD-InteractiveFictionGame/Room.cpp"
#include "../BAAD-InteractiveFictionGame/Game.cpp"
#include "../BAAD-InteractiveFictionGame/Alien.cpp"
#include "../BAAD-InteractiveFictionGame/Parser.cpp"
#include "../BAAD-InteractiveFictionGame/Actions.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
    *** Copied from object.h - so we know what we are testing ***
	Object(string n, string d, bool  takeable);
	Object(string n, string d, bool takeable, bool isLocked); //additional constructor for doors and maybe for other locked objects in the future
	string getName();
	string getDescription();
	bool isTakeable();
*/

namespace BAADInteractiveFictionGameTest
{
	TEST_CLASS(BAADInteractiveFictionGameTest)
	{
	public:

		TEST_METHOD(HelloMessage)
		{
			Logger::WriteMessage("Hello from BAAD_PlayerConstructor_Test\n");
		}

		TEST_METHOD(CreateRoom) { //precondition, room can be created, using the method of using variables for comparison.
			string id = "cryoTest";
			string name = "Test Room";
			string description = "A room for testing";
			Room* cryoTest = new Room(id, name, description);

			// Post condition, Verify the information retrieve for the random object, matches the information we provided on initialization;
			Assert::AreEqual(cryoTest->getId(), id, L"Verifying room ID");
			Assert::AreEqual(cryoTest->getName(), name, L"Verifying room name");
			Assert::AreEqual(cryoTest->getDescription(), description, L"Verifying description");
		}

		TEST_METHOD(AddObjectToRoom) {
			//first confirm room has no objects
			Room* cryoTest = new Room("cryoTest", "Test Room", "Test Description");
			cryoTest->printAllObjects(); //print nothing
			//add object
			Object* testObject = new Object("test object", "test description", true, true);
			cryoTest->addObject(testObject);
			cryoTest->printAllObjects(); //print test object
			Assert::AreEqual(testObject->getName(), cryoTest->getObject("test object")->getName(), L"Verifying object in room");
		}

		TEST_METHOD(AddTwoNeighboursAndVerifyDoorConnections) //precondition to create rooms and doors and set connections, post is to verify the rooms are properly connected.
		{
			//making the rooms
			Room* testRoom = new Room("test", "test", "test");
			Room* testNeighbour1 = new Room("testNeighbour1", "testNeighbour1", "testNeighbour1");
			Room* testNeighbour2 = new Room("testNeighbour2", "testNeighbour2", "testNeighbour2");

			//making the doors to connect the rooms
			Object* testDoor1 = new Object("testDoor1", "testDoor1", false, false);
			Object* testDoor2 = new Object("testDoor2", "testDoor2", false, false);

			//set the connected rooms
			testRoom->setNeighbour("testDoor1", testNeighbour1);
			testRoom->setNeighbour("testDoor2", testNeighbour2);

			//get the connected rooms by their names
			Room* testNeighbour1Getted = testRoom->getNeighbour("testDoor1");
			Room* testNeighbour2Getted = testRoom->getNeighbour("testDoor2");

			//check that the neighbour can be retrieved properly
			Assert::AreEqual(testNeighbour1->getName(), testNeighbour1Getted->getName(), L"testdoor1 should lead to testNeighbour1.");
			Assert::AreEqual(testNeighbour2->getName(), testNeighbour2Getted->getName(), L"testdoor2 should lead to testNeighbour2.");
		}
	
		TEST_METHOD(SameDoorName) //precondition to create rooms and doors and set connections, post is to verify the rooms are properly connected.
		{
			//making the rooms
			Room* testRoom = new Room("test", "test", "test");
			Room* testNeighbour1 = new Room("test", "test", "test");
			Room* testNeighbour2 = new Room("test", "test", "test");

			//making the doors to connect the rooms
			Object* testDoor1 = new Object("test", "test", false, false);

			//set the connected rooms
			testRoom->setNeighbour("test", testNeighbour1);
			testRoom->setNeighbour("test", testNeighbour2);

			// Retrieve neighbor using the same name
			Room* retrievedNeighbour = testRoom->getNeighbour("test");

			// Assert that the last set neighbor is returned
			Assert::AreEqual(testNeighbour2->getName(), retrievedNeighbour->getName(), L"test door should lead to testNeighbour2 (because of overwrite based on implementation).");
			
		};





		TEST_METHOD(VerifyRoomIsLockedAndBlockMovement) { //precondition is create two rooms connected by locked door //post is that goDoor doesn't let them change current room
			Parser parser; //to avoid external errors
			Alien alien; 
			Game game;

			//create needed objects for test
			Room* testRoom = new Room("test", "test", "test");
			Room* lockedRoom = new Room("lockedRoom", "lockedRoom", "lockedRoom");
			Object* lockedDoor = new Object("lockedDoor", "lockedDoor", false, false);//starting unlocked to manually set
			lockedDoor->setIsLocked(true); // lock the door manually
			testRoom->addObject(lockedDoor); //add the locked door
			testRoom->setNeighbour("lockedDoor", lockedRoom); //set the locked door as the connection point
			
			//check door is actually locked
			Assert::IsTrue(lockedDoor->getIsLocked(), L"The door should be locked.");
			game.setCurrentRoom(testRoom); //set inital position
			game.goDoor("lockedDoor"); //try moving through locked door and verify if they weren't able to move
			Assert::AreEqual(testRoom->getName(), game.getCurrentRoom()->getName(), L"Player should not move through a locked door.");
			}

		TEST_METHOD(VerifyRoomIsUnlockedAndAllowMovement) { //precondition is create two rooms connected by unlocked door //post is that goDoor does let them change current room
			Parser parser; //to avoid external errors
			Alien alien;
			Game game;

			//create needed objects for test
			Room* testRoom = new Room("test", "test", "test");
			Room* unlockedRoom = new Room("unlockedRoom", "unlockedRoom", "unlockedRoom");
			Object* unlockedDoor = new Object("unlockedDoor", "unlockedDoor", false, false); //needs to be unlocked to start, because of the silly bathroom hard code
			testRoom->addObject(unlockedDoor); //add the unlocked door
			testRoom->setNeighbour("unlockedDoor", unlockedRoom); //set the unlocked door as the connection point

			//check door is actually unlocked
			Assert::IsFalse(unlockedDoor->getIsLocked(), L"The door should be unlocked.");
			game.setCurrentRoom(testRoom); //set inital position
			game.goDoor("unlockedDoor"); //try moving through unlocked door and verify if they were able to move
			Assert::AreNotEqual(testRoom->getName(), game.getCurrentRoom()->getName(), L"Player should move through a unlocked door.");
		}


		TEST_METHOD(CreateObjects) {

			// create two different objects, but use variables to capture the information so we can compare later
			std::string messageOutput;
			string randomName = "Random";
			string randomDescription = "Random description";
			bool randomTake = false;
			string name2 = "Hello World";
			string name2Description = "Now is the time ...";
			bool helloTake = true;

			Object random(randomName, randomDescription, randomTake, false);
			Object n2(name2, name2Description, helloTake, false);

			// log object we are testing
			messageOutput = "Random object name " + random.getName() + "\n";

			// Verify the information retrieve for the random object, matches the information we provided on initialization
			Logger::WriteMessage(messageOutput.c_str());
			Assert::AreEqual(random.getName(), randomName, L"comparison of random object name");
			Assert::AreNotEqual(n2.getName(), randomName, L"comparing random object name is not same as n2 name");
			Assert::AreEqual(random.getDescription(), randomDescription, L"comparing random object description");
			Assert::IsFalse(random.getIsLocked(), L"testing random Object is unlocked by default");
			
			// 2nd object ...., maybe some more default testing
		}


		TEST_METHOD(RemoveObjectsFromInventory){
			// create two different objects, to delete 1 from inventory
			
			Object* test1 = new Object("test1", "test1", true, false);
			Object* test2 = new Object("test2", "test2", true, false);
			Inventory inventory;
			inventory.addObject(test1);
			inventory.addObject(test2);
			inventory.deleteObject(test1);
			Assert::IsFalse(inventory.gotObject("test1"), L"The object shouldn't be in the inventory");
			Assert::IsTrue(inventory.gotObject("test2"), L"The object should be in the inventory");

		}

		TEST_METHOD(FlashlightWorkingTest) { //precondition, flashlight is in inventory and turned off, post condition, it is now on
			Object* flashlight = new Object("flashlight", "test", true, false);
			Inventory inventory;
			inventory.addObject(flashlight);//add to inventory start off.
			flashlight->setWorking(false);
			Assert::IsFalse(flashlight->getIsWorking(), L"The flashlight should be off");
			flashlight->setWorking(true); //set on to verify this works
			Assert::IsTrue(flashlight->getIsWorking(), L"The flashlight should be on");
		}

		TEST_METHOD(CombineFlashlightAndBatteryToGetWorking) { //combines both by mimicing the combine logic from the game class, precondition is have both batteries and flashlight in inventory, post is the batteries are removed and the flashlight is turned on 
			Inventory inventory;
			//had to duplicate the combine code, because the game has its own private inventory.

			Object* batt = new Object("batteries", "test", true, false);
			Object* flash = new Object("flashlight", "test", true, false);
			inventory.addObject(flash);
			inventory.addObject(batt);
			flash->setWorking(false);			
			if (flash->getIsWorking()) { //test flashlight wasn't already working
				Assert::Fail(L"You already have a working flashlight.");
			}
			bool hasBatt = inventory.gotObject(batt->getName());
			bool hasFlash = inventory.gotObject(flash->getName());
			if (!hasBatt && !hasFlash) { //test both in inventory
				Assert::Fail(L"You do not have the flashlight and the batteries");
			}
			// Combine them
			inventory.deleteObject(batt);        // remove the batteries
			flash->setWorking(true);             // mark flashlight as working
			flash->setDescription("Working flashlight");
			Logger::WriteMessage(L"You combined the batteries with the flashlight");		//log they were combined	
			Assert::IsFalse(inventory.gotObject("batteries"), L"The batteries shouldn't be in the player's inventory"); //verify batteries removed
			Assert::IsTrue(flash->getIsWorking(), L"The Flashlight should be on"); //verify flashlight now works
		}

		TEST_METHOD(PasscodeDoorWorks) {
			Game game;
			Room* passcodeRoom = new Room("test", "test", "test");
			game.setCurrentRoom(passcodeRoom);
			Object* passcodeDoor = new Object("passcode door", "test", false, true);
			passcodeDoor->setIsPasscodeLocked(true);
			Assert::IsTrue(passcodeDoor->getIsPasscodeLocked(), L"Passcode door should require passcode");
			passcodeDoor->setPasscode(1234);
			game.typeCode(1234);
			Assert::IsTrue(passcodeDoor->getIsPasscodeLocked(), L"Player has not found both halves of a code"); //I would test unlocking but I cannot access the member for the foundcode1 and foundcode2

		}
		TEST_METHOD(PlayerCanHide) { //precondition player not hiding but in a room with a object they could hide in, post is player is hiding and can unhide, and then test alien leaves if player is hidden
			Game game;
			Object* locker = new Object("locker", "test", false, false, true); //create a safe zone that the player can hide in
			Room* testRoom = new Room("testRoom", "testRoom", "testRoom");
			Room* testRoom2 = new Room("testRoom", "testRoom", "testRoom");
			testRoom->addObject(locker); //add object to the room because you cannot hide when not in a room
			game.setCurrentRoom(testRoom);
			Assert::IsTrue(locker->getIsSafeZone(), L"Locker should be a safe place to hide"); //check it is safe
			Assert::IsFalse(game.getIsHidden(), L"Player should not be hidden");//check player isn't hiding in it
			game.hide("locker");
			Assert::IsTrue(game.getIsHidden(), L"Player should be hidden"); //check player now is hiding in it
			game.unhide();
			Assert::IsFalse(game.getIsHidden(), L"Player should not be hidden");//check player isn't hiding in anymore
			Alien alien; //add the alien
			alien.addRoom(testRoom);
			alien.addRoom(testRoom2);
			alien.setActive(true); //add rooms and set active
			game.hide("locker");
			alien.setCurrentRoom(testRoom); //put in room while player hidden
			alien.increaseTurnCounter(game.getCurrentRoom(), game.getIsHidden()); //since hiding it should leave
			Assert::IsFalse(alien.getSawPlayer(), L"Player is hiding, Alien should not see them");
			Assert::IsFalse((alien.getCurrentRoom() == testRoom), L"Alien should not be in the testRoom, as it should have gone out since the player hid");
		
		}

		TEST_METHOD(AddObjectsToInventory) {
			std::string messageOutput;
			string randomName = "Random";
			string randomDescription = "Random description";
			bool randomTake = false;
			string name2 = "Hello World";
			string name2Description = "Now is the time ...";
			bool helloTake = true;

			Object random(randomName, randomDescription, randomTake, false);
			Object n2(name2, name2Description, helloTake, false);
			Object n3(name2, name2Description, helloTake, false);

			/*
				*** copied from inventory.h ***
				void addObject(Object * object);
				Object* getObject(string objectName);
				bool gotObject(string objectName); // checks if the person has the items
			*/

			// create an inventory (e.g. player's inventory)
			Inventory player;

			// add a few objects to the player's inventory & verify the objects we added are indeed in the inventory
			player.addObject(&random);
			player.addObject(&n2);
			Assert::IsTrue(player.gotObject(randomName), L"Expected randomName to be in inventory, wasn't");
			Assert::IsTrue(player.gotObject(name2), L"Expected name2 to be in inventory, wasn't");
			Assert::IsFalse(player.gotObject("name"), L"didn't expect name to be in inventory, but WAS");

			// next let's verify the correct object is returned from getObject()
			string returnedName = (player.getObject(name2))->getName();
			Assert::AreEqual(returnedName, name2);

			// and for fun, compare the returned name to random's name - will intentionally fail the test case
			Assert::AreEqual(returnedName, randomName);
		}
	};
}