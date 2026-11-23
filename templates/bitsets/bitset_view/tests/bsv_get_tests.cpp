#include "bitsets/bitset_view/bsv_get.hpp"
#include "bsv_test_support.hpp"

TEST(BitsetViews, Get)
{
    auto check = []<typename Word, std::size_t extent>
    {
        constexpr auto width = std::numeric_limits<Word>::digits;
        constexpr Word even = std::numeric_limits<Word>::max() / 3;
        const std::array<Word, 3> words{even, static_cast<Word>(~even), even};
        BitsetView<const Word, extent> fixed{words.data()};
        BitsetView<const Word> dynamic{words.data(), extent};
        for (std::size_t i = 0; i != extent; ++i)
        {
            const bool expected = i % 2 == (i / width) % 2;
            if (bsv_get(fixed, i) != expected ||
                bsv_get(dynamic, i) != expected)
            {
                return false;
            }
        }
        return true;
    };
    EXPECT_TRUE(bsv_check_words(check));
}
