#include "3170_lexicographically_minimum_string_after_removing_stars.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::clearStars;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aaba*" "aab"

"abc" "abc"

"b*n" "n"

"abc*de*fgh*" "defgh"

"a*b*c*d*" ""

"abcde*f*" "cdef"

"d*yed" "yed"
)cases");

class t3170_lexicographically_minimum_string_after_removing_stars
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3170_lexicographically_minimum_string_after_removing_stars, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.clearStars(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3170_lexicographically_minimum_string_after_removing_stars,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
