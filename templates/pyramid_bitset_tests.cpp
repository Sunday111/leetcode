#include <algorithm>
#include <iterator>
#include <random>
#include <set>

#include "gtest/gtest.h"
#include "pyramid_bitset.hpp"

static_assert(PyramidBitset<1 << 20>::kTotalWords == 16384 + 256 + 4 + 1);

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
    PyramidBitset<1001, u64>,
    PyramidBitset<4096, u64>,
    PyramidBitset<13593, u64>,
    PyramidBitset<64 * 64 * 64, u64>>;

template <typename BitsetT>
class PyramidBitsetTypedFuzzyTest : public ::testing::Test
{
};

TYPED_TEST_SUITE(PyramidBitsetTypedFuzzyTest, BitsetCapacities);

TYPED_TEST(PyramidBitsetTypedFuzzyTest, NonEmptyMin)
{
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr auto capacity = Bitset::get_capacity();
    Bitset bs{kEmpty};

    EXPECT_TRUE(bs.is_empty());
    bs.add(cast<ValueType>(capacity - 1));
    ASSERT_FALSE(bs.is_empty());
    EXPECT_EQ(bs.min(), capacity - 1);
    bs.remove(cast<ValueType>(capacity - 1));
    EXPECT_TRUE(bs.is_empty());
}

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

    for (u32 t = 0; t != 4; ++t)
    {
        const u32 size = size_distr(rnd);
        std::uniform_int_distribution<u32> value_distr(0, size - 1);
        bs.initialize(kEmpty, capacity);
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

TYPED_TEST(PyramidBitsetTypedFuzzyTest, NeighbourSearch)
{
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr auto capacity = Bitset::get_capacity();
    Bitset bs{kEmpty};
    std::set<ValueType> reference;
    auto check = [&](ValueType v)
    {
        auto next = reference.upper_bound(v);
        auto prev = reference.lower_bound(v);
        EXPECT_EQ(bs.successor(v), next == reference.end() ? capacity : *next);
        EXPECT_EQ(
            bs.predecessor(v),
            prev == reference.begin() ? capacity : *std::prev(prev));
    };

    check(0);
    check(cast<ValueType>(capacity - 1));
    for (size_t boundary = 1; boundary < capacity;
         boundary *= Bitset::kWordSize)
    {
        for (auto v :
             {boundary - 1, boundary, std::min(boundary + 1, capacity - 1)})
        {
            bs.add(cast<ValueType>(v));
            reference.insert(cast<ValueType>(v));
        }
    }
    bs.add(cast<ValueType>(capacity - 1));
    reference.insert(cast<ValueType>(capacity - 1));
    for (auto v : reference) check(v);

    std::mt19937 rng{1569};
    std::uniform_int_distribution<size_t> values(0, capacity - 1);
    for (u32 i = 0; i != 1000; ++i)
    {
        auto v = cast<ValueType>(values(rng));
        if (reference.erase(v))
        {
            bs.remove(v);
        }
        else
        {
            bs.add(v);
            reference.insert(v);
        }
        check(v);
        check(cast<ValueType>(values(rng)));
    }

    bs.initialize(kFull);
    EXPECT_EQ(bs.predecessor(0), capacity);
    EXPECT_EQ(bs.successor(cast<ValueType>(capacity - 1)), capacity);
    for (u32 i = 0; i != 100; ++i)
    {
        auto v = cast<ValueType>(values(rng));
        EXPECT_EQ(bs.predecessor(v), v == 0 ? capacity : size_t{v} - 1);
        EXPECT_EQ(bs.successor(v), size_t{v} + 1);
    }
}
