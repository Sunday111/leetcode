#include "0132_palindrome_partitioning_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCut;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbab" 1
)cases");

class t0132_palindrome_partitioning_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0132_palindrome_partitioning_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minCut(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0132_palindrome_partitioning_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
