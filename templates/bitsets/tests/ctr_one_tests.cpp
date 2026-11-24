#include <gtest/gtest.h>

#include <concepts>

#include "bitsets/ctr_one.hpp"
#include "integral_aliases.hpp"

TEST(Bitsets, CountTrailingOnes)
{
    auto check = []<typename Word>
    {
        static_assert(std::same_as<decltype(::ctr_one(Word{})), u32>);
        constexpr u32 width = sizeof(Word) * 8;
        static_assert(::ctr_one(Word{}) == 0);
        static_assert(::ctr_one(static_cast<Word>(~Word{})) == width);
        for (u32 bit = 0; bit != width; ++bit)
        {
            EXPECT_EQ(::ctr_one(static_cast<Word>(~(Word{1} << bit))), bit);
        }
    };
    check.operator()<u8>();
    check.operator()<u16>();
    check.operator()<u32>();
    check.operator()<u64>();
    check.operator()<u128>();
}
