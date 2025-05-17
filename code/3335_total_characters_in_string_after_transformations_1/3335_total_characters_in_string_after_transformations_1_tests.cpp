#include "3335_total_characters_in_string_after_transformations_1.hpp"
#include "gtest/gtest.h"

TEST(t3335_total_characters_in_string_after_transformations_1, test_1)
{
    std::string_view input = "abcyy";
    constexpr unsigned t = 2;
    constexpr int expected = 7;
    ASSERT_EQ(Solution{}.lengthAfterTransformations(input, t), expected);
}

TEST(t3335_total_characters_in_string_after_transformations_1, test_2)
{
    std::string_view input = "azbk";
    constexpr unsigned t = 5;
    constexpr int expected = 5;
    ASSERT_EQ(Solution{}.lengthAfterTransformations(input, t), expected);
}

// TEST(t3335_total_characters_in_string_after_transformations_1, test_2)
// {
//     std::string_view input = "a";
//     for (unsigned i = 0; i <= 1'000; i += 26)
//     {
//         auto a = Solution{}.lengthAfterTransformations(input, i);
//         auto b = Solution{}.lengthAfterTransformations(input, i + 1);
//         std::println("{:4}: {:10} -> {:10} (delta: {:10})", i, a, b, b - a);
//     }
// }
