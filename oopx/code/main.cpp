#include <iostream>
#include <fstream>
#include <utility.hpp>
#include <binserial.hpp>
#include <bindeser.hpp>
using namespace std;
using namespace BinSerial;
int main()
{
    int a = 0xABCDEF;
    double score = 99.9;
    string file_name = "../data/testfile";
    // serialize(a, file_name);
    int b;
    // deserialize(b, file_name);
    cout << b << endl;
    std::cout << "Hello World!" << std::endl;
    return 0;
}