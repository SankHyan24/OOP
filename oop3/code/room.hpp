#pragma once
#include <iostream>
using namespace std;
class room
{
public:
    string name;
    string description;
    bool have_princess;
    bool have_monster;
    room() = default;
    room(string name, string description, bool have_princess, bool have_monster) : name(name), description(description), have_princess(have_princess), have_monster(have_monster) {}
    void set_room(string name, string description, bool have_princess, bool have_monster)
    {
        this->name = name;
        this->description = description;
        this->have_princess = have_princess;
        this->have_monster = have_monster;
    }
    void set_room(room r)
    {
        set_room(r.name, r.description, r.have_princess, r.have_monster);
    }
    void set_princess(bool have_princess)
    {
        this->have_princess = have_princess;
    }
    void set_monster(bool have_monster)
    {
        this->have_monster = have_monster;
    }
    void print_room() const
    {
        cout << "You entered the " << name << endl;
        cout << description << endl;
    }
};