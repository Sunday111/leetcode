#include "count_zeroes.hpp"

#include "gtest/gtest.h"

bool contains_zero(u32 v)
{
    while (v)
    {
        if ((v % 10) == 0) return true;
        v /= 10;
    }
    return false;
}

TEST(CountZeroesTest, Simple)
{
    std::vector<u32> counters;
    counters.push_back(0);

    while (counters.size() != 10'000)
    {
        u32 n = static_cast<u32>(counters.size());
        u32 count = counters.back() + contains_zero(n);
        counters.push_back(count);
        ASSERT_EQ(counters.back(), count_numbers_with_zeroes(n)) << "n = " << n;
    }
}
