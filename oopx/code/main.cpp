#include <iostream>
#include <fstream>
#include <binserial.hpp>
using namespace std;

int main()
{
    int64_t a = 0xABCDEF;
    double score = 99.9;
    string file_name = "../data/testfile";
    serialize(a, file_name);
    int64_t b;
    deserialize(b, file_name);
    cout << b << endl;
    std::cout << "Hello World!" << std::endl;
    return 0;
}