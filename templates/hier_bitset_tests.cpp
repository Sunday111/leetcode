#include <random>

#include "gtest/gtest.h"
#include "hier_bitset.hpp"

TEST(HierBitsetTest, Fuzzy)
{
    constexpr unsigned seed = 1234;
    constexpr u16 capacity = 13593;
    constexpr u16 min_size = capacity / 2;
    std::mt19937 rnd{seed};

    HierBitset<capacity> bs;  // NOLINT
    std::set<u32> std_set;
    std::uniform_int_distribution<u32> size_distr(min_size, capacity - 1);

    for (u32 t = 0; t != 500; ++t)
    {
        const u32 size = size_distr(rnd);
        std::uniform_int_distribution<u32> value_distr(0, size - 1);
        bs.clear(capacity);
        std_set.clear();

        for (u32 i = 0; i != 3 * size; ++i)
        {
            const u32 v = value_distr(rnd);
            ASSERT_EQ(bs.test(v), std_set.contains(v));
            if (bs.test(v))
            {
                bs.set<false>(v);
                std_set.erase(v);
            }
            else
            {
                bs.set<true>(v);
                std_set.insert(v);
            }

            ASSERT_EQ(std_set.empty(), bs.empty());
            if (!std_set.empty())
            {
                ASSERT_EQ(*std_set.begin(), bs.min());
                ASSERT_EQ(*std_set.rbegin(), bs.max());
            }
        }
    }
}
