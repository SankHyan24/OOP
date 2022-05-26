#include <xmlserial.hpp>
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
    remove(xmlPath);
    vector<tuple<int, double, string>> v_t1, v_t2;
    for (size_t i = 0; i < TEST_ARR_LEN / 10; i++)
        v_t1.push_back(make_tuple(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND),
                                  Utility::RandUtil::RandomDouble(0, 100),
                                  Utility::RandUtil::RandomString(10, '0', '9')));
    serialize(v_t1, "User", xmlPath);
}