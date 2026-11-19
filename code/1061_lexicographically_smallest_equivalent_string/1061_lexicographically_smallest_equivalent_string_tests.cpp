#include "1061_lexicographically_smallest_equivalent_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestEquivalentString;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"parker" "morris" "parser" "makkek"
)cases");

class t1061_lexicographically_smallest_equivalent_string
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1061_lexicographically_smallest_equivalent_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.smallestEquivalentString(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1061_lexicographically_smallest_equivalent_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
