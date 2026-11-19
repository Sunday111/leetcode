#include "3346_maximum_frequency_of_an_element_after_performing_operations_i.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFrequency;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,11,20,20] 5 1 2

[88,53] 27 2 2
)cases");

class t3346_maximum_frequency_of_an_element_after_performing_operations_i
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxFrequency(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
