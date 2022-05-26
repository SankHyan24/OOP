#include <xmlserial.hpp>
#include <xmldeser.hpp>
#include <utility.hpp>
#include <test.hpp>

#include <climits>
#include <random>
#include <map>
#include <list>
#include <vector>
#include <set>
using namespace std;
using namespace XMLSerial;

void xml_test()
{
    const char *xmlPath = "./test1.xml";
    const char *xmlPath1 = "./test11.xml";
    vector<tuple<int, string, string>> v_t1, v_t2;
    for (size_t i = 0; i < TEST_ARR_LEN / 10; i++)
    {
        tuple<int, string, string> tmp(i, Utility::RandUtil::RandomString(10, 'A', 'z'), Utility::RandUtil::RandomString(10, 'A', 'z'));
        v_t1.push_back(tmp);
    }
    serialize(v_t1, xmlPath, "std_vector");
    deserialize(v_t2, xmlPath, "std_vector");
    // for (auto &i : t1)
    // cout << i.first << " " << i.second << endl;
    ASSERT_EQ(v_t1, v_t2);
    serialize(v_t2, xmlPath1);
    cout << "end" << endl;
}