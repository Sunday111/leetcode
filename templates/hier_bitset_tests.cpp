#include <random>

#include "gtest/gtest.h"
#include "hier_bitset.hpp"

TEST(HierBitsetTest, Fuzzy)
{
    constexpr unsigned seed = 1234;
    constexpr u16 min_val = 0, max_val = 13593, capacity = max_val + 1;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr(min_val, max_val);

    HierBitset<capacity> bs;  // NOLINT
    std::set<u32> std_set;

    for (u32 t = 0; t != 50'000; ++t)
    {
        bs.init(capacity);
        std_set.clear();

        for (u32 i = 0; i != 50'000; ++i)
        {
            u32 v = distr(rnd);
            ASSERT_EQ(bs.test(v), std_set.contains(v));
            if (bs.test(v))
            {
                bs.clear(v);
                std_set.erase(v);
            }
            else
            {
                bs.set(v);
                std_set.insert(v);
            }
        }
    }
}
