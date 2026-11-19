#include "2514_count_anagrams.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, u32>(R"cases(
"too hot" 18
"b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp" 210324488
)cases");

class t2514_count_anagrams : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2514_count_anagrams, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [s] = inputs;
    ASSERT_EQ(expected, Solution{}.countAnagrams(s));
    ASSERT_EQ(expected, CachingFactorialsSolution{}.countAnagrams(s));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2514_count_anagrams,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
