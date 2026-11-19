#include <algorithm>
#include <print>

#include "0131_palindrome_partitioning.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string>,
    std::vector<std::vector<std::string>>>(R"cases(
"aab" [["a","a","b"],["aa","b"]]
"aaa" [["a","a","a"],["a","aa"],["aa","a"],["aaa"]]
)cases");

class t0131_palindrome_partitioning : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0131_palindrome_partitioning, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = Solution{}.partition(std::get<0>(inputs));
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0131_palindrome_partitioning,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
