#include "1838_frequency_of_the_most_frequent_element.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFrequency;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,4,8,13] 5 2
)cases");

class t1838_frequency_of_the_most_frequent_element
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1838_frequency_of_the_most_frequent_element, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxFrequency(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1838_frequency_of_the_most_frequent_element,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
