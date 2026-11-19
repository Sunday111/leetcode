#include "2761_prime_pairs_with_target_sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findPrimePairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 [[3,7],[5,5]]

2 []

100 [[3,97],[11,89],[17,83],[29,71],[41,59],[47,53]]
)cases");

class t2761_prime_pairs_with_target_sum
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2761_prime_pairs_with_target_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findPrimePairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2761_prime_pairs_with_target_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
