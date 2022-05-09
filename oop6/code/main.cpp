#include <vec.hpp>
#include <iostream>
using namespace std;
int main()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    v.clear();
    cout << v.empty() << endl;
    cout << v[3] << endl;
    cout << v.at(3) << endl;

    cout << "Hello, World!" << endl;
}