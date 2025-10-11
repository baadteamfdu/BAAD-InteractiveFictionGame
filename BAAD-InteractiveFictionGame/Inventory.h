#pragma once
#include <string>

class Object;

class Inventory 
{
public:
    Inventory();
    ~Inventory();

    bool addItem(const Object& obj);
    bool hasItem(const string& name) const;
    const Object* getItem(const string& name) const;
    string showInventory() const;

private:
    class Impl;
    Impl* impl_;
};

