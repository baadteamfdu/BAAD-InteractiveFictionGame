#include "Actions.h"
#include <string>
using namespace std;

Actions stringToAction(string action) { //maybe 
	
	if (action == "look") { //could allow for maybe eventual lists of synonyms
		return Actions::LOOK;
	}
	if (action == "take") {
		return Actions::TAKE; //saving for later
	}
	if (action == "use") {
		return Actions::USE; // saving for later
	}
	if (action == "open") {
		return Actions::OPEN; // saving for later
	}
	if (action == "go") {      //saving for later
		return Actions::GO;
	}	
	if (action == "type") {
		return Actions::TYPE;   //to return the type functionality
	}
	if (action == "help") {
		return Actions::HELP;
	}
	if (action == "inventory")
		return Actions::INVENTORY;

	return Actions::INVALID; //not yet sure if I need this
}
