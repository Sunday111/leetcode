#include "3713_longest_balanced_substring_i.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbac" 4

"nlllk" 3
)cases");

class t3713_longest_balanced_substring_i
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3713_longest_balanced_substring_i, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestBalanced(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3713_longest_balanced_substring_i,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
