#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bsv_test_support.hpp"

TEST(BitsetViews, StaticFill)
{
    auto check = []<typename Word, std::size_t extent>
    {
        constexpr auto width = sizeof(Word) * 8;
        constexpr Word pattern = static_cast<Word>(~Word{}) / 3;
        std::array<Word, 4> words{pattern, pattern, pattern, pattern};
        BitsetView<Word, extent> bits{words.data()};
        for (bool full : {true, false})
        {
            if (full)
            {
                bsv_fill<true>(bits);
            }
            else
            {
                bsv_fill<false>(bits);
            }
            for (std::size_t i = 0; i != words.size() * width; ++i)
            {
                bool bit = (words.at(i / width) >> (i % width)) & 1;
                if (bit != (i < extent ? full : i % 2 == 0))
                {
                    return false;
                }
            }
        }
        return true;
    };
    EXPECT_TRUE(bsv_check_words(check));
}
