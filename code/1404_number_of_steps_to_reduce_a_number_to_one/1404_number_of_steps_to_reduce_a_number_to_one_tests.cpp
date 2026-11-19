#include "1404_number_of_steps_to_reduce_a_number_to_one.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numSteps;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1101" 6

"11000" 6

"10" 1
)cases");

class t1404_number_of_steps_to_reduce_a_number_to_one
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1404_number_of_steps_to_reduce_a_number_to_one, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numSteps(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1404_number_of_steps_to_reduce_a_number_to_one,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
