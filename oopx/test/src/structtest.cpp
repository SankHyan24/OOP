#include <binserial.hpp>
#include <bindeser.hpp>
#include <utility.hpp>
#include <test.hpp>

#include <climits>
#include <random>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <tuple>

using namespace std;
using namespace BinSerial;
void struct_test()
{

    string file_name = "./testfile.tmp";

    tuple<int, double, string> t1, t2;
    get<0>(t1) = Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND);
    get<1>(t1) = Utility::RandUtil::RandomDouble(0, 100);
    string str1;
    Utility::RandUtil::RandomString(str1, TEST_STR_LEN);
    get<2>(t1) = str1;
    serialize(t1, file_name);
    deserialize(t2, file_name);
    ASSERT_EQ(get<0>(t1), get<0>(t2));
    ASSERT_EQ(get<1>(t1), get<1>(t2));
    ASSERT_EQ(get<2>(t1), get<2>(t2));

    remove(file_name.c_str());
    cout << "Test Done" << endl;
}