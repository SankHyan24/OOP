#include <iostream>
#include <fstream>
using namespace std;
template <typename T>
int serialize(T &t, const string &a)
{
    ofstream fout(a);
    if (!fout)
    {
        cout << "open file error" << endl;
        return -1;
    }
    fout << t;
    fout.close();
    return 0;
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}