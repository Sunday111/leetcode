#include "2749_minimum_operations_to_make_the_integer_zero.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::makeTheIntegerZero;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 -2 3
)cases");

class t2749_minimum_operations_to_make_the_integer_zero
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2749_minimum_operations_to_make_the_integer_zero, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.makeTheIntegerZero(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2749_minimum_operations_to_make_the_integer_zero,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
