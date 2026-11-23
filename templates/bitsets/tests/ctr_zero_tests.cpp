#include <gtest/gtest.h>

#include <cstdint>

#include "bitsets/ctr_zero.hpp"

TEST(Bitsets, CountTrailingZeroes)
{
    auto check = []<typename Word>
    {
        constexpr int width = sizeof(Word) * 8;
        static_assert(::ctr_zero(Word{}) == width);
        static_assert(::ctr_zero(static_cast<Word>(~Word{})) == 0);
        for (int bit = 0; bit != width; ++bit)
        {
            EXPECT_EQ(::ctr_zero(static_cast<Word>(Word{1} << bit)), bit);
        }
    };
    check.operator()<std::uint8_t>();
    check.operator()<std::uint16_t>();
    check.operator()<std::uint32_t>();
    check.operator()<std::uint64_t>();
}
