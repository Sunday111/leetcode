#include "2427_number_of_common_factors.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::commonFactors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
12 6 4

25 30 2
)cases");

class t2427_number_of_common_factors : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2427_number_of_common_factors, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.commonFactors(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2427_number_of_common_factors,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
