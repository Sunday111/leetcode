#include "2014_longest_subsequence_repeated_k_times.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<std::tuple<std::string, u16>, std::string>(R"cases(
"letsleetcode" 2 "let"
"bb" 2 "b"
"ab" 2 ""
"nhsbbeonhsbbeonhsbbeo" 3 "nhsbbeo"
"gbjbjigjbji" 2 "gjbji"
)cases");

class t2014_longest_subsequence_repeated_k_times : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2014_longest_subsequence_repeated_k_times, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [s, k] = inputs;
    ASSERT_EQ(expected, Solution3{}.longestSubsequenceRepeatedK(s, k));
}
INSTANTIATE_TEST_SUITE_P(Gen, t2014_longest_subsequence_repeated_k_times, ::testing::Range(size_t{0}, kCases.size()), [](const testing::TestParamInfo<size_t>& info) { return "C" + std::to_string(info.index); });
