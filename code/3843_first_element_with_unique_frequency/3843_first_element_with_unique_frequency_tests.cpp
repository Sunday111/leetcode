#include "3843_first_element_with_unique_frequency.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int>(R"cases(
[20,10,30,30] 30

[20,20,10,30,30,30] 20

[10,10,20,20] -1
)cases");

class t3843_first_element_with_unique_frequency
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3843_first_element_with_unique_frequency, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.firstUniqueFreq(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3843_first_element_with_unique_frequency,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
