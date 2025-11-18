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