#include "0273_integer_to_english_words.hpp"
#include "gtest/gtest.h"

// TEST(t0273_integer_to_english_words, test_1)
// {
//     Solution s{};
//     ASSERT_EQ(s.numberToWords(123), "One Hundred Twenty Three");
// }

// TEST(t0273_integer_to_english_words, test_2)
// {
//     Solution s{};
//     ASSERT_EQ(
//         s.numberToWords(12345),
//         "Twelve Thousand Three Hundred Forty Five");
// }

// TEST(t0273_integer_to_english_words, test_3)
// {
//     Solution s{};
//     ASSERT_EQ(
//         s.numberToWords(1234567),
//         "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty "
//         "Seven");
// }

TEST(t0273_integer_to_english_words, test_4)
{
    Solution s{};
    ASSERT_EQ(
        s.numberToWords(1234567891),
        "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven "
        "Thousand Eight Hundred Ninety One");
}
