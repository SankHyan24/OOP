#include <vec.hpp>  // to test
#include <iostream> // for std::cout
#include <ctime>    // for random number generation
#include <assert.h> // for assert to test the code
using namespace std;
/**
 * Function main
 * This function is used to test all the
 * functions in the vec.hpp file.
 *
 * In this file, all the functions are tested by assert.
 * If the assert fails, the test will fail.
 * If this program output "Test Passed",
 * it means that all the test are passed.
 *
 * to test .at()'s exception, you can decomment the line 57
 */
int main()
{
    // set the test utility
    srand(time(NULL));
    // test_num1/2 is used to test the constructor.
    size_t test_num1 = 10000, test_num2 = 100;
    auto v_int = new int[test_num1];

    // test the constructors
    Vector<int> v;

    // test the push_back method
    for (size_t i = 0; i < test_num1; i++)
    {
        v_int[i] = rand() % test_num1;
        v.push_back(v_int[i]);
        assert(v.size() == i + 1);
        assert(v[i] == v_int[i]);
    }

    // test the at method
    for (size_t i = 0; i < test_num1; i++)
    {
        int r = rand() % test_num1;
        assert(v.at(r) == v_int[r]);
    }
    for (size_t i = 0; i < test_num1; i++)
    {
        v_int[i] = rand() % test_num1;
        v.at(i) = v_int[i];
        assert(v.at(i) == v_int[i]);
    }

    // test the size method
    assert(v.size() == test_num1);
    v.clear();
    assert(v.size() == 0);
    assert(v.empty());
    /** decomment the next line, and it will throw an error */
    // assert(v.at(test_id) == v_int[test_id]);
    delete[] v_int;

    // test the copy constructor on other class
    Vector<string> v2(test_num2);
    assert(v2.size() == test_num2);
    assert(!v2.empty());
    for (size_t i = 0; i < test_num2; i++)
    {
        v2[i] = "test" + to_string(i * i);
        assert(v2[i] == "test" + to_string(i * i));
    }
    auto v3(v2);
    assert(v3.size() == test_num2);
    assert(!v3.empty());
    for (size_t i = 0; i < test_num2; i++)
        assert(v3[i] == "test" + to_string(i * i));

    // assert(false);
    cout << "Test Passed" << endl;
    return 0;
}
