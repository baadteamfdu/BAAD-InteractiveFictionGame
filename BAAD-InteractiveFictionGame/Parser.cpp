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
        if (action == Actions::HIDE && word == "in") { //if the word is in it will ignore it and then read the rest of the line
            word = "";
            if (getline(spaceSplitter, word)) {
                noun = word;
            }
        }
        if (action == Actions::WAKE && word == "up"){
            //wake up captain
            word = "";
            if (getline(spaceSplitter, word)) {
                noun = word;
            }
        }
    
    }
    else {
        noun = "";
    }
    if (getline(spaceSplitter, word, ' ')) //added what the keycard will be used on to allow for use keycard cryo door// serve water to captain
    {
        if (word == "on" || word == "to") { //if the word is on it will ignore it and then read the rest of the line
            word = "";
            if (getline(spaceSplitter, word)) {
                whatToUseOn = word;
            }    
        }
        else { //if the word is not on add the word that wasn't on and then just add everything else too.
            whatToUseOn = word;
            if (getline(spaceSplitter, word)) {
                whatToUseOn += " " + word;
            }
        }
    }
    else {
        whatToUseOn = "";
    }
    if (action == Actions::OPEN || action == Actions::GO || action == Actions::PEEK) { //moves the whatToUseOn to the end of the noun so you can go through a multi word door instead
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