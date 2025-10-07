#include "Parser.h"
#include "Actions.h"
#include <string>
#include <sstream>
using namespace std;

bool Parser::parse(string input, Actions &action, string &noun) {
    for (size_t i = 0; i < input.size(); i++) {
        input[i] = tolower(input[i]); // if its a uppercase command the program lowers it so that it triggers the right function.
    }
    //maybe include something that makes it not case sensitive, could also add special cases here for specific two word or one word inputs
    stringstream spaceSplitter(input); //https://www.geeksforgeeks.org/cpp/getline-string-c/
    string word;
        getline(spaceSplitter, word, ' '); //should only check the first two words then return true or false, might not work idk
        action = stringToAction(word);
        if (getline(spaceSplitter, word, ' '))
        {
            noun = word;
        }
        else {
            
            noun = "";
        }
        if (action == Actions::INVALID) {
            return false;
        }
        else {
            return true;
        }
}