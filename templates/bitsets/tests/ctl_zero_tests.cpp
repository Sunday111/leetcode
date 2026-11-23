#include <gtest/gtest.h>

#include <cstdint>

#include "bitsets/ctl_zero.hpp"

TEST(Bitsets, CountLeadingZeroes)
{
    auto check = []<typename Word>
    {
        constexpr int width = sizeof(Word) * 8;
        static_assert(::ctl_zero(Word{}) == width);
        static_assert(::ctl_zero(static_cast<Word>(~Word{})) == 0);
        for (int bit = 0; bit != width; ++bit)
        {
            EXPECT_EQ(
                ::ctl_zero(static_cast<Word>(Word{1} << bit)),
                width - 1 - bit);
        }
    };
    check.operator()<std::uint8_t>();
    check.operator()<std::uint16_t>();
    check.operator()<std::uint32_t>();
    check.operator()<std::uint64_t>();
}
