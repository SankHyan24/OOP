#pragma once

#include <assert.h>
#define ASSERT(MESSAGE, VALUE) assert((VALUE) && (MESSAGE))
#define ASSERT_EQ(VALUE_1, VALUE_2) assert((VALUE_1) == (VALUE_2))
#define ASSERT_NE(VALUE_1, VALUE_2) assert((VALUE_1) != (VALUE_2))