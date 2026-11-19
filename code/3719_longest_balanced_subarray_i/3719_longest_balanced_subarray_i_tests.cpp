#include "3719_longest_balanced_subarray_i.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,5,4,3] 4

[3,2,2,5,4] 5

[1,2,3,2] 3
)cases");

class t3719_longest_balanced_subarray_i
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3719_longest_balanced_subarray_i, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestBalanced(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3719_longest_balanced_subarray_i,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
