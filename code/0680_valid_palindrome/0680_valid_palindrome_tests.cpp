#include "0680_valid_palindrome.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, bool>(R"cases(
"cupuuffuupucu" true
"deeee" true
)cases");

class t0680_valid_palindrome : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0680_valid_palindrome, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    ASSERT_EQ(expected, Solution{}.validPalindrome(std::get<0>(inputs)));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0680_valid_palindrome,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
