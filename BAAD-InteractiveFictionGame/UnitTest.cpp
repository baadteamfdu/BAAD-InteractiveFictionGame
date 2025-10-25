#include "UnitTest.h"

void UnitTest::alienTest() {
	Game game;
	game.init();  // initializes rooms, objects, etc.

	// create an alien - let's call her alice
	Alien alice;
	setupAlienRooms(alice);
	cout << "alice object created\n";

	// activate the alien - note: some Tech debt here, game.cpp activates alien when player moves to a new room (if not already active)
	//   plus - currently requires a separate command to go to a room - could conceivably do all this in the constructor
	//   ? why even have an active / inactive state for the alien?

	alice.setAlienIsACtive(true);
	alice.relocateAlienToANewRoom();   // DeCos moveAlientoANewRoom - not needed - works fine w/ relocate

	// should now be all set to try out some tests
	// 
	// does alien switch rooms after specified # of turns
	int turnsBeforeSwitching = alice.getNumMovesBeforeAlienChangesRooms();
	std::cout << "Alien is expected to move in " << turnsBeforeSwitching << " turns\n";
	std::cout << " Alien is hiding in: " << alice.getAliensCurrentRoom() << endl;
	std::cout << "  Player is currently in: " << game.getCurrentRoom()->getId() << 
		" and kill# is " << alice.getNumMovesB4PlayerDies() << endl;
	for (int turnCounter = 1; turnCounter < turnsBeforeSwitching + 2; turnCounter++) {
		std::cout << "Turn " << turnCounter << endl;
		alice.increaseTurnCounter(game.getCurrentRoom());  // passes in players current room
		std::cout << " Alien is in: " << alice.getAliensCurrentRoom() << endl;
	}

	// now let's run a bunch of iterations, tightening up the prints
	for (int turnCounter = 1; turnCounter < 25; turnCounter++) {
		std::cout << "switch# " << alice.getNumMovesBeforeAlienChangesRooms() <<
			"\t turn " << turnCounter <<
			"\t Alice in " << alice.getAliensCurrentRoom() << endl;
		alice.increaseTurnCounter(game.getCurrentRoom());
	}

	// move the alien to the same room as the player and see if the player gets killed
	cout << "\n*** Testing kill function ***\n";
	alice.moveAlienToSpecificRoom(game.getCurrentRoom());
	for (int turnCounter = 1; turnCounter < 10; turnCounter++) {
		std::cout << "Alice in " << alice.getAliensCurrentRoom() << 
			"\t switch# " << alice.getNumMovesBeforeAlienChangesRooms() <<
			"\t Cohab counter = " << alice.getTimeInRoomCounter() <<
			"\t turn " << turnCounter <<
			endl;
		alice.increaseTurnCounter(game.getCurrentRoom());
	}



	char dummyChar;
	cin >> dummyChar;  // pause program so actual code doesn't kick in

}

// LV - for alien class unit testing - provide method to set up rooms alien can visit
void UnitTest::setupAlienRooms(Alien& alien) {
    alien.addRoom(cryoStart);
    alien.addRoom(cryoHall);
    alien.addRoom(escapePod);
    alien.addRoom(workersRoom);
    alien.addRoom(bathroom);
    alien.addRoom(finalRoom);
}
