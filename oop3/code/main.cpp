#include <iostream>
#include <game.hpp>
using namespace std;
class B
{
public:
    int id;
    B()
    {
        id = 0;
        cout << "B()" << endl;
    }
    B(int id) : id(id)
    {
        cout << "B::B(int id)" << endl;
    }
    ~B()
    {
        cout << "~B()" << endl;
    }
};
class A
{
    B i;

public:
    // : i(0)
    A()
    {
        cout << "A::A()" << endl;
    }
    ~A()
    {
        cout << "A::~A()" << endl;
        cout << get();
    }
    void set(int i) const {}
    int get()
    {
        return i.id;
    }
};

int main()
{
    const A a;
    a.set(1);
    return 0;
}

// int main()
// {
//     // auto map = new game;
//     // map->game_process();

//     cout << "hello, world!" << endl;
//     return 0;
// }