#include <gtest/gtest.h>

#include <cstdint>

#include "bitsets/ctr_one.hpp"

TEST(Bitsets, CountTrailingOnes)
{
    auto check = []<typename Word>
    {
        constexpr int width = sizeof(Word) * 8;
        static_assert(::ctr_one(Word{}) == 0);
        static_assert(::ctr_one(static_cast<Word>(~Word{})) == width);
        for (int bit = 0; bit != width; ++bit)
        {
            EXPECT_EQ(::ctr_one(static_cast<Word>(~(Word{1} << bit))), bit);
        }
    };
    check.operator()<std::uint8_t>();
    check.operator()<std::uint16_t>();
    check.operator()<std::uint32_t>();
    check.operator()<std::uint64_t>();
}
