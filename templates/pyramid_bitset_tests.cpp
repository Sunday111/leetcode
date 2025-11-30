#include <random>
#include <set>

#include "gtest/gtest.h"
#include "pyramid_bitset.hpp"

// List of capacities we want to test
using BitsetCapacities = ::testing::Types<
    PyramidBitset<1, u8>,
    PyramidBitset<256, u8>,
    PyramidBitset<1024, u16>,
    PyramidBitset<16 * 16 * 16, u16>,
    PyramidBitset<1024, u32>,
    PyramidBitset<4096, u32>,
    PyramidBitset<13593, u32>,
    PyramidBitset<32 * 32 * 32, u32>,
    PyramidBitset<1024, u64>,
    PyramidBitset<4096, u64>,
    PyramidBitset<13593, u64>,
    PyramidBitset<64 * 64 * 64, u64>>;

template <typename BitsetT>
class PyramidBitsetTypedFuzzyTest : public ::testing::Test
{
};

TYPED_TEST_SUITE(PyramidBitsetTypedFuzzyTest, BitsetCapacities);

TYPED_TEST(PyramidBitsetTypedFuzzyTest, Fuzzy)
{
    constexpr unsigned seed = 1234;
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr u32 capacity = Bitset::get_capacity();
    constexpr u32 min_size = capacity / 2;
    std::mt19937 rnd{seed};

    Bitset bs;
    std::set<ValueType> std_set;
    std::uniform_int_distribution<u32> size_distr(min_size, capacity - 1);

    for (u32 t = 0; t != 10; ++t)
    {
        const u32 size = size_distr(rnd);
        std::uniform_int_distribution<u32> value_distr(0, size - 1);
        bs.initialize(capacity);
        std_set.clear();

        for (u32 i = 0; i != 3 * size; ++i)
        {
            const auto v = cast<ValueType>(value_distr(rnd));
            ASSERT_EQ(bs.get(v), std_set.contains(v));
            if (bs.get(v))
            {
                bs.template set<false>(v);
                std_set.erase(v);
            }
            else
            {
                bs.template set<true>(v);
                std_set.insert(v);
            }

            ASSERT_EQ(std_set.empty(), bs.is_empty());
            if (!std_set.empty())
            {
                ASSERT_EQ(*std_set.begin(), bs.min());
                ASSERT_EQ(*std_set.rbegin(), bs.max());
            }
        }
    }
}
