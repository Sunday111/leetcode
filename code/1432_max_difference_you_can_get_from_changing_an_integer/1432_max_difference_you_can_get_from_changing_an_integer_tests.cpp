#include "1432_max_difference_you_can_get_from_changing_an_integer.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxDiff;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
111 888
)cases");

class t1432_max_difference_you_can_get_from_changing_an_integer
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1432_max_difference_you_can_get_from_changing_an_integer, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxDiff(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1432_max_difference_you_can_get_from_changing_an_integer,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
