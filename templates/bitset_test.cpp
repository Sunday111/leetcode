#include <random>

#include "bitsets.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"

template <typename Trait>
class BitsetTest : public ::testing::Test
{
public:
    inline static constexpr auto traits = Trait{};
};

TYPED_TEST_SUITE_P(BitsetTest);

TYPED_TEST_P(BitsetTest, FuzzyGetAndSet)
{
    constexpr unsigned seed = 1234;
    constexpr u32 bitset_size = 10'000;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr(0, bitset_size - 1);

    Bitset<bitset_size, std::decay_t<decltype(*this)>::traits> my_bitset;
    std::bitset<bitset_size> std_bitset;

    for (u32 i = 0; i != 50'000; ++i)
    {
        u32 index = distr(rnd);
        ASSERT_EQ(std_bitset[index], my_bitset.Get(index));
        bool value = distr(rnd) & 1;
        std_bitset[index] = value;
        my_bitset.Set(index, value);

        for (u32 j = 0; j != bitset_size; ++j)
        {
            ASSERT_EQ(std_bitset[j], my_bitset.Get(j));
        }
    }
}

REGISTER_TYPED_TEST_SUITE_P(BitsetTest, FuzzyGetAndSet);

struct TrBranchless
{
    static constexpr std::string_view name = "branchless";
    using Word = uint64_t;
    static constexpr bool branchless = true;
};

struct TrBranches
{
    static constexpr std::string_view name = "branches";
    using Word = uint64_t;
    static constexpr bool branchless = false;
};

struct TraitNamePrinter
{
    template <typename T>
    static std::string GetName(int)
    {
        return std::string{T::name};
    }
};

// Define which configurations to test
using BitsetConfigs = ::testing::Types<TrBranches, TrBranchless>;

INSTANTIATE_TYPED_TEST_SUITE_P(
    Bitset,
    BitsetTest,
    BitsetConfigs,
    TraitNamePrinter);
