#include "Actions.h"
#include <string>
using namespace std;

Actions stringToAction(string action) { //maybe 

	if (action == "look" || action == "view" || action == "inspect") { //could allow for maybe eventual lists of synonyms
		return Actions::LOOK;
	}
	if (action == "take" || action == "grab" || action == "get") {
		return Actions::TAKE; //saving for later
	}
	if (action == "use" || action == "utilize" || action == "apply" || action == "operate" || action == "wield" || action == "manipulate" || action == "combine" || action == "click") {
		return Actions::USE; // saving for later
	}
	if (action == "open") {
		return Actions::OPEN; //don't think much would work for synonyms for open
	}
	if (action == "go" || action == "travel" || action == "move" || action == "proceed" || action == "walk" || action == "journey" || action == "advance") {
		return Actions::GO;
	}
	if (action == "type" || action == "input") {
		return Actions::TYPE;   //to return the type functionality
	}
	if (action == "map")
	{
		return Actions::MAP;
	}
	if (action == "peek") {
		return Actions::PEEK;
	}
	if (action == "help") {
		return Actions::HELP;
	}
	if (action == "inventory") {
		return Actions::INVENTORY;
	}
	if (action == "hide") {
		return Actions::HIDE;
	}
	if (action == "unhide" || action == "exit" || action == "leave") {
		return Actions::UNHIDE;
	}
	if (action == "press") {
		return Actions::PRESS;
	}
	if (action == "run") {
		return Actions::RUN;
	}
	if (action == "wake" || action == "awaken") {
		return Actions::WAKE;
	}
	if (action == "serve" || action == "give") {
		return Actions::SERVE;
	}
	if (action == "read") {
		return Actions::READ;
	}
	if (action == "talk" || action == "speak" || action == "ask") {
		return Actions::TALK;
	}
		return Actions::INVALID; //not yet sure if I need this
}
