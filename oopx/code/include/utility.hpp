#pragma once
#include <random>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <typeinfo>
#include <cxxabi.h> // 所需头文件

/**
 * Namespace: Utility
 * Description: Contains utility functions
 */

template <typename T>
struct TypeParseTraits;

#define REGISTER_PARSE_TYPE(X)   \
    template <>                  \
    struct TypeParseTraits<X>    \
    {                            \
        static const char *name; \
    };                           \
    const char *TypeParseTraits<X>::name = #X

namespace Utility
{
    /**
     * Class RandUtil
     * Description: Random number generator
     * Functions:
     *  - RandomInt64: generate a random 64-bit integer
     *  - RandomInt: generate a random 32-bit integer
     *  - RandomDouble: generate a random double
     *  - RandomString: generate a random string
     */
    class RandUtil
    {
    public:
        static int64_t RandomInt64(int64_t min, int64_t max)
        {
            static std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<int64_t> dis(min, max);
            return dis(gen);
        }
        static int RandomInt(int min, int max)
        {
            static std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<int> dis(min, max);
            return dis(gen);
        }
        static double RandomDouble(double min, double max)
        {
            static std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_real_distribution<double> dis(min, max);
            return dis(gen);
        }
        static void RandomString(std::string &buf, size_t len)
        {
            static std::random_device rd;
            std::default_random_engine rng(rd());
            std::uniform_int_distribution<char> uniform_dist(0);
            buf.clear();
            for (size_t i = 0; i < len; i++)
                buf.push_back(uniform_dist(rng));
        }
        static std::string RandomString(size_t len)
        {
            static std::random_device rd;
            std::default_random_engine rng(rd());
            std::uniform_int_distribution<char> uniform_dist(0);
            std::string buf;
            for (size_t i = 0; i < len; i++)
                buf.push_back(uniform_dist(rng));
            return buf;
        }
        static std::string RandomString(size_t len, char low, char high)
        {
            static std::random_device rd;
            std::default_random_engine rng(rd());
            std::uniform_int_distribution<char> uniform_dist(low, high);
            std::string buf;
            for (size_t i = 0; i < len; i++)
                buf.push_back(uniform_dist(rng));
            return buf;
        }
    };

    template <typename T>
    int tuple_len(T val)
    {
        return (std::tuple_size<T>::value);
    }

}
