#pragma once
#include <random>
#include <iostream>
#include <algorithm>

namespace utility
{
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
    };
}
