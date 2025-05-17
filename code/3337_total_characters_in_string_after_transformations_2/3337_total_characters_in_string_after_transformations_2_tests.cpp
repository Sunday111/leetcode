#include "3337_total_characters_in_string_after_transformations_2.hpp"
#include "gtest/gtest.h"

TEST(t3337_total_characters_in_string_after_transformations_2, test_1)
{
    constexpr std::string_view s = "abcyy";
    constexpr uint32_t r = 2;
    std::vector nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
    ASSERT_EQ(Solution{}.lengthAfterTransformations(s, r, nums), 7);
}

TEST(t3337_total_characters_in_string_after_transformations_2, test_2)
{
    constexpr std::string_view s = "azbk";
    constexpr uint32_t r = 1;
    std::vector nums = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    ASSERT_EQ(Solution{}.lengthAfterTransformations(s, r, nums), 8);
}

TEST(t3337_total_characters_in_string_after_transformations_2, test_3)
{
    constexpr std::string_view s =
        "abcyrsmtfyjhnvhvrtmhvvngvmkempcvepbgxxbeebyhy";
    constexpr uint32_t r = 999;
    std::vector nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
    ASSERT_EQ(Solution{}.lengthAfterTransformations(s, r, nums), 869688536);
}
