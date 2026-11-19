#include "0438_find_all_anagrams_in_a_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"cbaebabacd" "abc" [0,6]

"abab" "ab" [0,1,2]
)cases");

class t0438_find_all_anagrams_in_a_string
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0438_find_all_anagrams_in_a_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findAnagrams(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0438_find_all_anagrams_in_a_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
