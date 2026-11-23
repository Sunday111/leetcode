#include "bitsets/bitset_view/bsv_set.hpp"
#include "bsv_test_support.hpp"

TEST(BitsetViews, Set)
{
    auto check = []<typename Word, std::size_t extent>
    {
        constexpr auto width = std::numeric_limits<Word>::digits;
        std::array<Word, 3> words{};
        BitsetView<Word, extent> fixed{words.data()};
        BitsetView<Word> dynamic{words.data(), extent};
        for (std::size_t i = 0; i != extent; ++i)
        {
            std::array<Word, 3> expected{};
            expected.at(i / width) = static_cast<Word>(Word{1} << (i % width));
            bsv_set<true>(fixed, i);
            if (words != expected)
            {
                return false;
            }
            bsv_set<false>(dynamic, i);
            if (words != std::array<Word, 3>{})
            {
                return false;
            }
        }
        return true;
    };
    EXPECT_TRUE(bsv_check_words(check));
}
