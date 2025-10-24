#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include "../BAAD-InteractiveFictionGame/Object.cpp"
#include "../BAAD-InteractiveFictionGame/Inventory.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*

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
		TEST_METHOD(CreateObjects) {
			std::string messageOutput;
			string randomName = "Random";
			string randomDescription = "Random description";
			bool randomTake = false;
			string name2 = "Hello World";
			string name2Description = "Now is the time ...";
			bool helloTake = true;

			Object random(randomName, randomDescription, randomTake);
			Object n2(name2, name2Description, helloTake);
			// log object we are testing
			messageOutput = "Random object name " + random.getName() + "\n";
			Logger::WriteMessage(messageOutput.c_str());
			Assert::AreEqual(random.getName(), randomName, L"comparison of random object name");
			Assert::AreNotEqual(n2.getName(), randomName, L"comparing random object name is not same as n2 name");
			Assert::AreEqual(random.getDescription(), randomDescription, L"comparing random object description");
			Assert::IsFalse(random.getIsLocked(), L"testing random Object is unlocked by default");
			// 2nd object ...., maybe some more default testing
		}

		TEST_METHOD(AddObjectsToInventory) {
			std::string messageOutput;
			string randomName = "Random";
			string randomDescription = "Random description";
			bool randomTake = false;
			string name2 = "Hello World";
			string name2Description = "Now is the time ...";
			bool helloTake = true;

			Object random(randomName, randomDescription, randomTake);
			Object n2(name2, name2Description, helloTake);
			Object n3(name2, name2Description, helloTake);

			// void addObject(Object * object);
			// 	Object* getObject(string objectName);
			// bool gotObject(string objectName); // checks if the person has the items
			Inventory player;
			player.addObject(&random);
			player.addObject(&n2);
			Assert::IsTrue(player.gotObject(randomName), L"Expected randomName to be in inventory, wasn't");
			Assert::IsTrue(player.gotObject(name2), L"Expected name2 to be in inventory, wasn't");
			Assert::IsFalse(player.gotObject("name"), L"didn't expect name to be in inventory, but WAS");

			// next let's verify the correct object is returned from getObject()
			string returnedName = (player.getObject(name2))->getName();
			Assert::AreEqual(returnedName, name2);
			// and for fun, compare the returned name to random's name
			Assert::AreEqual(returnedName, randomName);
		}
	};
}