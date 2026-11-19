#include "3704_count_no_zero_pairs_that_sum_to_n.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countNoZeroPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1000000000000000 50891681057058
)cases");

class t3704_count_no_zero_pairs_that_sum_to_n
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3704_count_no_zero_pairs_that_sum_to_n, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countNoZeroPairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3704_count_no_zero_pairs_that_sum_to_n,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
