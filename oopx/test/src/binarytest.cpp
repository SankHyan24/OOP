#include <binserial.hpp>
#include <utility.hpp>
using namespace std;
void binary_test()
{
    int64_t a = 0xABCDEF;
    double score = 99.9;
    string file_name = "../data/testfile";
    serialize(a, file_name);
    int64_t b;
    deserialize(b, file_name);
    ASSERT_EQ(a, b);
}