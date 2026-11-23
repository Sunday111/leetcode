#include "bitsets/bitset_view/bsv_count.hpp"
#include "bsv_test_support.hpp"

TEST(BitsetViews, DynamicCount)
{
    auto check = []<typename Word, std::size_t extent>
    {
        constexpr Word pattern = std::numeric_limits<Word>::max() / 3;
        std::array<Word, 4> words{pattern, pattern, pattern, pattern};
        BitsetView<const Word> bits{words.data(), extent};
        if (bsv_count(bits) != (extent + 1) / 2)
        {
            return false;
        }
        words.fill(0);
        if (bsv_count(bits) != 0)
        {
            return false;
        }
        words.fill(std::numeric_limits<Word>::max());
        return bsv_count(bits) == extent;
    };
    EXPECT_TRUE(bsv_check_words(check));
}
