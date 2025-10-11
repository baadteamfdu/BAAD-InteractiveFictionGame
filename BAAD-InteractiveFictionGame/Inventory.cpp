#include "Inventory.h"
#include "Object.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// Helper functions
namespace 
{
    string trim(string s) 
{
        auto is_not_space = [](unsigned char ch){ return !isspace(ch); };
        s.erase(s.begin(), find_if(s.begin(), s.end(), is_not_space));
        s.erase(find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
        return s;
    }
    string lower(string s) 
{
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c){ return static_cast<char>(tolower(c)); });
        return s;
    }
    string norm(string s) { return lower(trim(s)); }
}

class Inventory::Impl 
{
public:
    vector<Object> items;
};

Inventory::Inventory() : impl_(new Impl) {}
Inventory::~Inventory() { delete impl_; }

bool Inventory::addItem(const Object& obj) 
{
    string key = norm(obj.getName());
    bool dup = any_of(impl_->items.begin(), impl_->items.end(),
        [&](const Object& o){ return norm(o.getName()) == key; });
    if (dup) return false;
    impl_->items.push_back(obj);
    return true;
}

bool Inventory::hasItem(const string& name) const 
{
    string key = norm(name);
    return any_of(impl_->items.begin(), impl_->items.end(),
        [&](const Object& o){ return norm(o.getName()) == key; });
}

const Object* Inventory::getItem(const string& name) const 
{
    string key = norm(name);
    auto it = find_if(impl_->items.begin(), impl_->items.end(),
        [&](const Object& o){ return norm(o.getName()) == key; });
    return (it == impl_->items.end()) ? nullptr : &*it;
}

string Inventory::showInventory() const 
{
    if (impl_->items.empty()) return "Your inventory is empty.";
    ostringstream out;
    out << "Inventory:\n";
    for (const auto& o : impl_->items)
        out << " - " << o.getName() << "\n";
    return out.str();
}
