#include <binserial.hpp>
#include <utility.hpp>
#include <test.hpp>
#include <random>
#define TEST_STR_LEN 10
using namespace std;
using namespace BinSerial;
void binary_test()
{

    string file_name = "./testfile.tmp";

    for (size_t i = 0; i < TEST_STR_LEN; i++)
    {
        int64_t int_b, int_a = utility::RandUtil::RandomInt64(0, 100);
        serialize(int_a, file_name);
        deserialize(int_b, file_name);
        ASSERT_EQ(int_a, int_b);
    }

    for (size_t i = 0; i < TEST_STR_LEN; i++)
    {
        double score2, score = utility::RandUtil::RandomDouble(0, 100);
        serialize(score, file_name);
        deserialize(score2, file_name);
        ASSERT_EQ(score, score2);
    }

    for (size_t i = 0; i < TEST_STR_LEN; i++)
    {
        string str1, str2;
        utility::RandUtil::RandomString(str1, 10);
        serialize(str1, file_name);
        deserialize(str2, file_name);
        ASSERT_EQ(str1, str2);
    }

    remove(file_name.c_str());
}