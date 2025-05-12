#include "0017_letter_combinations_of_a_phone_number.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

TEST(t0017_letter_combinations_of_a_phone_number, test_1)
{
    constexpr std::string_view input = "23";
    std::vector<std::string>
        expected{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    std::vector<std::string> actual = Solution{}.letterCombinations(input);
    ASSERT_EQ(sorted(expected), sorted(actual));
}
