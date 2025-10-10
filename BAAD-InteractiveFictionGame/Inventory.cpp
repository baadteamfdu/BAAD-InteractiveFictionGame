using namespace std;
#include "Inventory.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_map>

struct Item 
{
    string name;         // display name, e.g., "keycard"
    string description;  // optional: "Level A Access card"
};

class Inventory 
{
public:
    // Insert item by its lowercase key (derived from name). Returns false if it already exists.
    bool add(const Item& it) 
    {
        string key = toKey(it.name);
        auto [ignored, inserted] = items.emplace(key, it);
        return inserted;
    }

    // Remove an item by name/key (case-insensitive). Returns true if removed.
    bool remove(const string& nameOrKey) 
    {
        return items.erase(toKey(nameOrKey)) > 0;
    }

    // Check presence by name/key (case-insensitive).
    bool has(const string& nameOrKey) const 
    {
        return items.find(toKey(nameOrKey)) != items.end();
    }

    // Get const pointer to item (nullptr if not found).
    const Item* get(const string& nameOrKey) const 
    {
        auto it = items.find(toKey(nameOrKey));
        return it == items.end() ? nullptr : &it->second;
    }

    // List all items (stable alphabetical by display name).
    vector<Item> list() const 
    {
        vector<Item> out;
        out.reserve(items.size());
        for (auto& kv : items) out.push_back(kv.second);
        sort(out.begin(), out.end(), [](const Item& a, const Item& b) 
            {
            string al = toKey(a.name), bl = toKey(b.name);
            if (al == bl) return a.name < b.name; // tie-break by original casing
            return al < bl;
            });
        return out;
    }

    // Print a user-facing view of the inventory.
    void print(ostream& os = cout) const 
    {
        auto all = list();
        if (all.empty()) 
        {
            os << "Your inventory is empty.\n";
            return;
        }
        os << "Inventory:\n";
        for (auto& it : all) os << " - " << it.name << "\n";
    }

    // Clear all items.
    void clear() { items.clear(); }

    // Count
    size_t size() const { return items.size(); }

    // Utility: convert arbitrary string to the canonical key.
    static string toKey(string s) 
    {
        // trim
        auto isSpace = [](unsigned char c) { return std::isspace(c); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&](char c) { return !isSpace((unsigned char)c); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [&](char c) { return !isSpace((unsigned char)c); }).base(), s.end());
        // lowercase
        for (char& c : s) c = (char)std::tolower((unsigned char)c);
        return s;
    }

private:
    unordered_map<string, Item> items; // key: lowercase item name
};
