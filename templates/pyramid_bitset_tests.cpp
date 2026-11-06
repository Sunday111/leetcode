#include <algorithm>
#include <iterator>
#include <limits>
#include <random>
#include <set>
#include <type_traits>

#include "cast.hpp"
#include "gtest/gtest.h"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_add_ex.hpp"
#include "pyramid_bitset/pbs_add_if.hpp"
#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_max.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_next.hpp"
#include "pyramid_bitset/pbs_next_inclusive.hpp"
#include "pyramid_bitset/pbs_prev.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "pyramid_bitset/pbs_remove_ex.hpp"
#include "pyramid_bitset/pbs_set.hpp"

static_assert(PyramidBitset<1 << 20>::kTotalWords == 16384 + 256 + 4 + 1);
static_assert(std::is_pointer_v<decltype(PyramidBitset<1 << 20>::words)>);
static_assert(std::is_array_v<std::remove_reference_t<
                  decltype(PyramidBitset<1 << 20>::kLayersSizes)>>);
static_assert(
    std::is_array_v<
        std::remove_reference_t<decltype(PyramidBitset<1 << 20>::offsets)>>);

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
    constexpr auto capacity = Bitset::kCapacity;
    typename Bitset::WordType storage[Bitset::kTotalWords]{};
    const auto bs = pbs_make<Bitset::kCapacity>(storage);

    EXPECT_TRUE(pbs_is_empty(bs));
    pbs_add(bs, cast<ValueType>(capacity - 1));
    ASSERT_FALSE(pbs_is_empty(bs));
    EXPECT_EQ(pbs_min(bs), capacity - 1);
    pbs_remove(bs, cast<ValueType>(capacity - 1));
    EXPECT_TRUE(pbs_is_empty(bs));
}

TYPED_TEST(PyramidBitsetTypedFuzzyTest, FreeOperations)
{
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr auto last = cast<ValueType>(Bitset::kCapacity - 1);
    typename Bitset::WordType storage[Bitset::kTotalWords]{};
    const auto bs = pbs_make<Bitset::kCapacity>(storage);
    pbs_add_if(bs, last, false);
    EXPECT_TRUE(pbs_is_empty(bs));
    EXPECT_TRUE(pbs_add_ex(bs, last));
    EXPECT_FALSE(pbs_add_ex(bs, last));
    EXPECT_EQ(pbs_max(bs), last);
    EXPECT_TRUE(pbs_remove_ex(bs, last));
    EXPECT_FALSE(pbs_remove_ex(bs, last));
    pbs_add_if(bs, last, true);
    EXPECT_TRUE(pbs_get(bs, last));
    pbs_set(bs, last, false);
    EXPECT_TRUE(pbs_is_empty(bs));
    pbs_set<true>(bs, last);
    EXPECT_EQ(pbs_min(bs), last);
    pbs_set<false>(bs, last);
    EXPECT_TRUE(pbs_is_empty(bs));
    pbs_initialize<true>(bs);
    EXPECT_TRUE(pbs_get(bs, last));
    pbs_initialize(bs, kEmpty);
    EXPECT_TRUE(pbs_is_empty(bs));
    pbs_set(bs, last, true);
    EXPECT_TRUE(pbs_get(bs, last));
    pbs_initialize<false>(bs);
    EXPECT_TRUE(pbs_is_empty(bs));
}

TYPED_TEST(PyramidBitsetTypedFuzzyTest, Fuzzy)
{
    constexpr unsigned seed = 1234;
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr u32 capacity = Bitset::kCapacity;
    constexpr u32 min_size = capacity / 2;
    std::mt19937 rnd{seed};

    typename Bitset::WordType storage[Bitset::kTotalWords]{};
    const auto bs = pbs_make<Bitset::kCapacity>(storage);
    std::set<ValueType> std_set;
    std::uniform_int_distribution<u32> size_distr(min_size, capacity - 1);

    for (u32 t = 0; t != 4; ++t)
    {
        const u32 size = size_distr(rnd);
        std::uniform_int_distribution<u32> value_distr(0, size - 1);
        pbs_initialize(bs, kEmpty, capacity);
        std_set.clear();

        for (u32 i = 0; i != 3 * size; ++i)
        {
            const auto v = cast<ValueType>(value_distr(rnd));
            ASSERT_EQ(pbs_get(bs, v), std_set.contains(v));
            if (pbs_get(bs, v))
            {
                pbs_set<false>(bs, v);
                std_set.erase(v);
            }
            else
            {
                pbs_set<true>(bs, v);
                std_set.insert(v);
            }

            ASSERT_EQ(std_set.empty(), pbs_is_empty(bs));
            if (!std_set.empty())
            {
                ASSERT_EQ(*std_set.begin(), pbs_min(bs));
                ASSERT_EQ(*std_set.rbegin(), pbs_max(bs));
            }
        }
    }
}

TYPED_TEST(PyramidBitsetTypedFuzzyTest, NeighbourSearch)
{
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr auto capacity = Bitset::kCapacity;
    typename Bitset::WordType storage[Bitset::kTotalWords]{};
    const auto bs = pbs_make<Bitset::kCapacity>(storage);
    std::set<ValueType> reference;
    auto check = [&](ValueType v)
    {
        auto next = reference.upper_bound(v);
        auto prev = reference.lower_bound(v);
        EXPECT_EQ(pbs_next(bs, v), next == reference.end() ? capacity : *next);
        EXPECT_EQ(
            pbs_next_inclusive(bs, v),
            prev == reference.end() ? capacity : *prev);
        EXPECT_EQ(
            pbs_prev(bs, v),
            prev == reference.begin() ? capacity : *std::prev(prev));
    };

    check(0);
    check(cast<ValueType>(capacity - 1));
    for (size_t boundary = 1; boundary < capacity;
         boundary *= Bitset::kWordSize)
    {
        for (auto v :
             {boundary - 1,
              boundary,
              std::min<size_t>(boundary + 1, capacity - 1)})
        {
            pbs_add(bs, cast<ValueType>(v));
            reference.insert(cast<ValueType>(v));
        }
    }
    pbs_add(bs, cast<ValueType>(capacity - 1));
    reference.insert(cast<ValueType>(capacity - 1));
    for (auto v : reference) check(v);

    std::mt19937 rng{1569};
    std::uniform_int_distribution<size_t> values(0, capacity - 1);
    for (u32 i = 0; i != 1000; ++i)
    {
        auto v = cast<ValueType>(values(rng));
        if (reference.erase(v))
        {
            pbs_remove(bs, v);
        }
        else
        {
            pbs_add(bs, v);
            reference.insert(v);
        }
        check(v);
        check(cast<ValueType>(values(rng)));
    }

    pbs_initialize(bs, kFull);
    EXPECT_EQ(pbs_prev(bs, 0), capacity);
    EXPECT_EQ(pbs_next(bs, cast<ValueType>(capacity - 1)), capacity);
    for (u32 i = 0; i != 100; ++i)
    {
        auto v = cast<ValueType>(values(rng));
        EXPECT_EQ(pbs_prev(bs, v), v == 0 ? capacity : size_t{v} - 1);
        EXPECT_EQ(pbs_next(bs, v), size_t{v} + 1);
        EXPECT_EQ(pbs_next_inclusive(bs, v), v);
    }
}

using InclusiveNextCapacities = ::testing::Types<
    PyramidBitset<1>,
    PyramidBitset<63>,
    PyramidBitset<64>,
    PyramidBitset<65>,
    PyramidBitset<255>,
    PyramidBitset<256>,
    PyramidBitset<257>,
    PyramidBitset<65535>,
    PyramidBitset<65536>,
    PyramidBitset<100000>>;

template <typename BitsetT>
class PyramidBitsetInclusiveNextTest : public ::testing::Test
{
};

TYPED_TEST_SUITE(PyramidBitsetInclusiveNextTest, InclusiveNextCapacities);

TYPED_TEST(PyramidBitsetInclusiveNextTest, BoundariesAndSentinel)
{
    using Bitset = TypeParam;
    using ValueType = typename Bitset::ValueType;
    constexpr auto capacity = Bitset::kCapacity;
    constexpr ValueType last = capacity - 1;
    static constexpr
        typename Bitset::WordType empty_words[Bitset::kTotalWords]{};
    constexpr auto empty = pbs_make<capacity>(empty_words);
    static_assert(std::is_same_v<
                  decltype(pbs_next_inclusive(empty, ValueType{})),
                  UintForValue<capacity>>);
    static_assert(pbs_next_inclusive(empty, ValueType{}) == capacity);
    static_assert(pbs_next_inclusive(empty, last) == capacity);

    typename Bitset::WordType storage[Bitset::kTotalWords]{};
    const auto bs = pbs_make<Bitset::kCapacity>(storage);
    EXPECT_EQ(pbs_next_inclusive(bs, 0), capacity);
    EXPECT_EQ(pbs_next_inclusive(bs, last), capacity);

    pbs_add(bs, last);
    EXPECT_EQ(pbs_next_inclusive(bs, 0), last);
    EXPECT_EQ(pbs_next_inclusive(bs, last), last);
    pbs_remove(bs, last);
    EXPECT_EQ(pbs_next_inclusive(bs, 0), capacity);

    pbs_add(bs, 0);
    EXPECT_EQ(pbs_next_inclusive(bs, 0), 0);
    if constexpr (capacity > 1)
    {
        EXPECT_EQ(pbs_next_inclusive(bs, 1), capacity);
    }
    pbs_remove(bs, 0);

    for (u32 boundary = Bitset::kWordSize; boundary < capacity;
         boundary *= Bitset::kWordSize)
    {
        const ValueType at = boundary & std::numeric_limits<ValueType>::max();
        const ValueType before =
            (boundary - 1) & std::numeric_limits<ValueType>::max();
        pbs_add(bs, at);
        EXPECT_EQ(pbs_next_inclusive(bs, before), at);
        EXPECT_EQ(pbs_next_inclusive(bs, at), at);
        pbs_remove(bs, at);
        EXPECT_EQ(pbs_next_inclusive(bs, before), capacity);
    }

    pbs_initialize(bs, kFull);
    EXPECT_EQ(pbs_next_inclusive(bs, last), last);
    pbs_remove(bs, last);
    EXPECT_EQ(pbs_next_inclusive(bs, last), capacity);
}
