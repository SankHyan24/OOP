#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        count++;
        cout << "A(), with " << count << " objects" << endl;
    }
    A(const A &)
    {
        count++;
        cout << "A(const A&), with " << count << " objects" << endl;
    }
    ~A()
    {
        count--;
        cout << "~A(), with " << count << " objects" << endl;
    }
    void print_addr()
    {
        cout << "address of this object: " << this << endl;
    }
    static int count;
};
int A::count = 0;

A f(A a)
{
    cout << "f(A a)" << endl;
    return a;
}

int main()
{
    A a;
    a.print_addr();
    A b = f(a);
    b.print_addr();
    return 0;
}