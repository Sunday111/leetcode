#include "1768_merge_strings_alternately_simple.hpp"
#include "1768_merge_strings_alternately_sse2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::string>(R"cases(
"abc" "pqr" "apbqcr"
"ab" "pqrs" "apbqrs"
"abcd" "pq" "apbqcd"
)cases");

class t1768_merge_strings_alternately : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1768_merge_strings_alternately, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [a, b] = inputs;
    ASSERT_EQ(expected, simple::Solution{}.mergeAlternately(a, b));
}
TEST_P(t1768_merge_strings_alternately, DISABLED_Sse2)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [a, b] = inputs;
    ASSERT_EQ(expected, solution_sse2::Solution{}.mergeAlternately(a, b));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1768_merge_strings_alternately,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
