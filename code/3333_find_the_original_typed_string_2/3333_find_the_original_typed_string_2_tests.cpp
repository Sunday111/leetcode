#include "3333_find_the_original_typed_string_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::possibleStringCount;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aabbccdd" 7 5

"aaabbb" 3 8

"d" 1 1
)cases");

class t3333_find_the_original_typed_string_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3333_find_the_original_typed_string_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.possibleStringCount(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3333_find_the_original_typed_string_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
