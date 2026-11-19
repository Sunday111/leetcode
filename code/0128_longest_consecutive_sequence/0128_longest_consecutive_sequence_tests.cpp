#include "0128_longest_consecutive_sequence.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestConsecutive;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[100,4,200,1,3,2] 4

[0,-1] 2
)cases");

class t0128_longest_consecutive_sequence
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0128_longest_consecutive_sequence, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestConsecutive(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0128_longest_consecutive_sequence,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
