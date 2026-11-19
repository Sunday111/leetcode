#include "0029_divide_two_integers.hpp"
#include "0029_divide_two_integers_msb.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int, int>, int>(R"cases(
10 3 3
7 -3 -2
0 1 0
-2147483648 -1 2147483647
-2147483648 1 -2147483648
-2147483648 -2147483648 1
)cases");

class t0029_divide_two_integers : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0029_divide_two_integers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto [a, b] = inputs;
    ASSERT_EQ(expected, Solution::divide(a, b));
    ASSERT_EQ(expected, SolutionMSB::divide(a, b));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0029_divide_two_integers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
