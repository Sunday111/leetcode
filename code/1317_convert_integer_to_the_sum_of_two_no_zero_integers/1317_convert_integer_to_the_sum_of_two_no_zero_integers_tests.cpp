#include "1317_convert_integer_to_the_sum_of_two_no_zero_integers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int>, int>(R"cases(
2 2
11 11
10000 10000
)cases");

class t1317_convert_integer_to_the_sum_of_two_no_zero_integers
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1317_convert_integer_to_the_sum_of_two_no_zero_integers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = Solution{}.getNoZeroIntegers(std::get<0>(inputs));
    ASSERT_EQ(actual.size(), 2);
    ASSERT_EQ(actual[0] + actual[1], expected);
    for (int value : actual)
    {
        ASSERT_GT(value, 0);
        ASSERT_EQ(std::to_string(value).find('0'), std::string::npos);
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1317_convert_integer_to_the_sum_of_two_no_zero_integers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
