#include <random>
#include <set>

#include "gtest/gtest.h"
#include "hier_bitset.hpp"

// List of capacities we want to test
using BitsetCapacities = ::testing::Types<
    HierBitset<1, u8>,
    HierBitset<256, u8>,
    HierBitset<1024, u16>,
    HierBitset<16 * 16 * 16, u16>,
    HierBitset<1024, u32>,
    HierBitset<4096, u32>,
    HierBitset<13593, u32>,
    HierBitset<32 * 32 * 32, u32>,
    HierBitset<1024, u64>,
    HierBitset<4096, u64>,
    HierBitset<13593, u64>,
    HierBitset<64 * 64 * 64, u64>>;

template <typename BitsetT>
class HierBitsetTypedFuzzyTest : public ::testing::Test
{
};

TYPED_TEST_SUITE(HierBitsetTypedFuzzyTest, BitsetCapacities);

TYPED_TEST(HierBitsetTypedFuzzyTest, Fuzzy)
{
    constexpr unsigned seed = 1234;
    using Bitset = TypeParam;
    constexpr u32 capacity = Bitset::capacity();  // template parameter
    constexpr u32 min_size = capacity / 2;
    std::mt19937 rnd{seed};

    Bitset bs;
    std::set<u32> std_set;
    std::uniform_int_distribution<u32> size_distr(min_size, capacity - 1);

    for (u32 t = 0; t != 10; ++t)
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
                bs.template set<false>(v);
                std_set.erase(v);
            }
            else
            {
                bs.template set<true>(v);
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
