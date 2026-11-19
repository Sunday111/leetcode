#include "0022_generate_parentheses.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint8_t>, std::vector<std::string>>(
        R"cases(
3 ["((()))","(()())","(())()","()(())","()()()"]
1 ["()"]
)cases");

class t0022_generate_parentheses : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0022_generate_parentheses, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = Solution{}.generateParenthesis(std::get<0>(inputs));
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0022_generate_parentheses,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
