#include "3734.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexPalindromicPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"baba"
"abba"
"baab"

"baba"
"bbaa"
""

"abc"
"abb"
""

"aac"
"abb"
"aca"

"a"
"z"
""
)");

class t3734 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3734, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3734,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
