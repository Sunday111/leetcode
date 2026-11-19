#include "2246_longest_path_with_different_adjacent_characters.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestPath;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[-1,0,0,1,1,2] "abacbe" 3

[-1,0,0,0] "aabc" 3
)cases");

class t2246_longest_path_with_different_adjacent_characters
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2246_longest_path_with_different_adjacent_characters, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestPath(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2246_longest_path_with_different_adjacent_characters,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
