#include "Parser.h"
#include "Actions.h"
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

bool Parser::parse(string input, Actions &action, string &noun, string &whatToUseOn) {
    for (size_t i = 0; i < input.size(); i++) {
        input[i] = tolower(input[i]); // if its a uppercase command the program lowers it so that it triggers the right function.
    }
    //maybe include something that makes it not case sensitive, could also add special cases here for specific two word or one word inputs
    stringstream spaceSplitter(input); //https://www.geeksforgeeks.org/cpp/getline-string-c/
    string word;
    if (getline(spaceSplitter, word, ' ')) { //should only check the first two words then return true or false, might not work idk
        action = stringToAction(word);
    }
    if (getline(spaceSplitter, word, ' '))
    {
        noun = word;
    }
    else {
        noun = "";
    }
    if (getline(spaceSplitter, word)) //added what the keycard will be used on to allow for use keycard cryo door
    {
        whatToUseOn = word;
    }
    else {
        whatToUseOn = "";
    }
    if (action == Actions::OPEN || action == Actions::GO) { //moves the whatToUseOn to the end of the noun so you can go through a multi word door instead
        if (!whatToUseOn.empty()) {                         //it being noun = cryo whatToUseOn = door
            noun += " " + whatToUseOn;
            whatToUseOn = "";
        }
    }
    if (action == Actions::INVALID) {
        return false;
    }
    else {
        return true;
    }

}