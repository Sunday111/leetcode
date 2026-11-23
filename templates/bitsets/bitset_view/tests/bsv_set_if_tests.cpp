#include "bitsets/bitset_view/bsv_set_if.hpp"
#include "bsv_test_support.hpp"

TEST(BitsetViews, ConditionalUpdateReturnsAffectedWord)
{
    auto check = []<typename Word>
    {
        constexpr auto width = sizeof(Word) * 8;
        Word words[]{7, 2};
        BitsetView<Word, width + 2> bits{words};
        EXPECT_EQ(bsv_set_if<true>(bits, width, false), 2);
        EXPECT_EQ(bsv_set_if<true>(bits, width, true), 3);
        EXPECT_EQ(bsv_set_if<false>(bits, width + 1, false), 3);
        EXPECT_EQ(bsv_set_if<false>(bits, width + 1, true), 1);
        EXPECT_EQ(words[0], 7);
        EXPECT_EQ(words[1], 1);
    };
    check.operator()<std::uint8_t>();
    check.operator()<std::uint16_t>();
    check.operator()<std::uint32_t>();
    check.operator()<std::uint64_t>();
}
