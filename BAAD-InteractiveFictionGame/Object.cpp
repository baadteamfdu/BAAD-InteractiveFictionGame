#include "Object.h"
#include <string>
#include <utility>

using namespace std;

Object::Object(string name, string description, bool isTakeable)
    : name_(move(name)), description_(move(description)), isTakeable_(isTakeable) {}

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
    return isTakeable_;
}
