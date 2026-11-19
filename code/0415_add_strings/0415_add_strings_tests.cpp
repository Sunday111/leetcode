#include "0415_add_strings.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addStrings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11" "123" "134"

"1" "9" "10"
)cases");

class t0415_add_strings : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0415_add_strings, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.addStrings(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0415_add_strings,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
