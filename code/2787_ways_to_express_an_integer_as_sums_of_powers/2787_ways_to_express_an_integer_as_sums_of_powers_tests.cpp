#include "2787_ways_to_express_an_integer_as_sums_of_powers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 2 1
)cases");

class t2787_ways_to_express_an_integer_as_sums_of_powers
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2787_ways_to_express_an_integer_as_sums_of_powers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numberOfWays(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2787_ways_to_express_an_integer_as_sums_of_powers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
