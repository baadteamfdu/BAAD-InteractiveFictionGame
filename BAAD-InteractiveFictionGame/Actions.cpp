#include "Actions.h"
#include <string>
using namespace std;

Actions stringToAction(string action) { //maybe 
	if (action == "look") { //could allow for maybe eventual lists of synonyms
		return Actions::LOOK;
	}
	if (action == "take") {
		return Actions::TAKE;
	}
	if (action == "use") {
		return Actions::USE;
	}
	if (action == "open") {
		return Actions::OPEN;
	}
	if (action == "go") {
		return Actions::GO;
	}	
	return Actions::INVALID; //not yet sure if I need this
}