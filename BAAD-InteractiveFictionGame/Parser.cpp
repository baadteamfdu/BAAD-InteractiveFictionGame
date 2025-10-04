#include "Parser.h"
#include "Actions.h"
#include <string>
#include <sstream>
using namespace std;

bool Parser::parse(string input, Actions action, string noun) {
    //maybe include something that makes it not case sensitive, could also add special cases here for specific two word or one word inputs
    stringstream spaceSplitter(input); //https://www.geeksforgeeks.org/cpp/getline-string-c/
    string word;
        getline(spaceSplitter, word, ' ');
        action = stringToAction(word);
        getline(spaceSplitter, word, ' ');
        noun = word;
        if (action == Actions::INVALID) {
            return false;
        }
        else {
            return true;
        }
}