#include <gtest/gtest.h>

#include <concepts>

#include "bitsets/ctl_zero.hpp"
#include "integral_aliases.hpp"

TEST(Bitsets, CountLeadingZeroes)
{
    auto check = []<typename Word>
    {
        static_assert(std::same_as<decltype(::ctl_zero(Word{})), u32>);
        constexpr u32 width = sizeof(Word) * 8;
        static_assert(::ctl_zero(Word{}) == width);
        static_assert(::ctl_zero(static_cast<Word>(~Word{})) == 0);
        for (u32 bit = 0; bit != width; ++bit)
        {
            EXPECT_EQ(
                ::ctl_zero(static_cast<Word>(Word{1} << bit)),
                width - 1 - bit);
        }
    };
    check.operator()<u8>();
    check.operator()<u16>();
    check.operator()<u32>();
    check.operator()<u64>();
    check.operator()<u128>();
}
