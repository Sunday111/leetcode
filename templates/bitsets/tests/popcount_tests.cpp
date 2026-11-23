#include <gtest/gtest.h>

#include "bitsets/popcount.hpp"

static_assert(BitsetWord<const unsigned int>);
static_assert(!BitsetWord<bool>);
static_assert(!BitsetWord<int>);
static_assert(!BitsetWord<char16_t>);

TEST(Bitsets, Popcount)
{
    auto check = []<typename Word>
    {
        constexpr Word all = static_cast<Word>(~Word{});
        constexpr int width = sizeof(Word) * 8;
        static_assert(popcount(Word{0}) == 0);
        static_assert(popcount(all) == width);
        static_assert(popcount(static_cast<Word>(all / 3)) == width / 2);
        EXPECT_EQ(popcount(static_cast<Word>(Word{1} << (width - 1))), 1);
    };
    check.operator()<unsigned char>();
    check.operator()<unsigned short>();
    check.operator()<unsigned int>();
    check.operator()<unsigned long long>();
}
