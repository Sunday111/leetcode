#include "2563_count_the_number_of_fair_pairs.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countFairPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,7,4,4,5] 3 6 6
)cases");

class t2563_count_the_number_of_fair_pairs
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2563_count_the_number_of_fair_pairs, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countFairPairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2563_count_the_number_of_fair_pairs,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
