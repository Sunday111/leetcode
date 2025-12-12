// #include "2048_next_greater_numerically_balanced_number.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"

bool is_balanced(u32 v)
{
    std::array<u8, 10> freq{};
    while (v)
    {
        ++freq[v % 10];
        v /= 10;
    }

    for (u8 i = 0; i != 10; ++i)
    {
        if (freq[i] && freq[i] != i) return false;
    }

    return true;
}

TEST(t2048_next_greater_numerically_balanced_number, DISABLED_precompute)
{
    std::vector<u32> balanced;
    for (u32 i = 0; i != 2'000'001; ++i)
    {
        if (is_balanced(i))
        {
            balanced.push_back(i);
        }
    }

    std::println("balanced: {}", balanced);
}
