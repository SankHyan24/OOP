#pragma once
// test utils
#include <cassert>
#define ASSERT(MESSAGE, VALUE) assert((VALUE) && (MESSAGE))
#define ASSERT_EQ(VALUE_1, VALUE_2) assert((VALUE_1) == (VALUE_2))
#define ASSERT_STREQ(VALUE_1, VALUE_2) assert((std::to_string(VALUE_1)) == (std::to_string(VALUE_2)))
#define ASSERT_NE(VALUE_1, VALUE_2) assert((VALUE_1) != (VALUE_2))
// constants and types
const int TEST_STR_LEN = 10;
const int TEST_ARR_LEN = 100;
const int INT_UP_BOUND = 100;
const int INT_LOW_BOUND = 0;
// declare the test subfunction which will nbe used in the test_main function
void binary_test();
void xml_test();
void struct_test();