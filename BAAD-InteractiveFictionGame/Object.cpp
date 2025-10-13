// Object.cpp
#include "Object.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace 
{
    // Normalize helper: trim + lowercase (for robust comparisons)
    string normalize(string s) 
    {
        auto is_not_space = [](unsigned char ch) { return !isspace(ch); };
        s.erase(s.begin(), find_if(s.begin(), s.end(), is_not_space));
        s.erase(find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
        transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return s;
    }
}

Object::Object(string name, string description, bool takeable)
    : name_(move(name)),
    description_(move(description)),
    takeable_(takeable),
    taken_(false) {}

const string& Object::getName() const 
{
    return name_;
}

const string& Object::getDescription() const 
{
    return description_;
}

bool Object::isTakeable() const 
{
    return takeable_;
}

bool Object::isTaken() const 
{
    return taken_;
}

void Object::setTaken(bool value) 
{
    taken_ = value;
}

bool Object::matchesName(const string& query) const 
{
    return normalize(name_) == normalize(query);
}

//use inheritance for object types like takeable maybe and maybe exits/door and the base class could have things like id name and description etc

Object::Object(string name, string description, bool takeable) :name (name), description(description), takeable(takeable){}

string Object::getName() { return name; }
string Object::getDescription() { return description; }
bool Object::isTakeable() { return takeable; }
