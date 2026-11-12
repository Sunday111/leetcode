#include "1520.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumOfSubstrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bdacdcba"                     ["bdacdcba"]
"a"                            ["a"]
"aaaa"                         ["aaaa"]
"abc"                          ["a","b","c"]
"abcdefghijklmnopqrstuvwxyz"   ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
"aabbcc"                       ["aa","bb","cc"]
"ababcdcd"                     ["abab","cdcd"]
"abbaccd"                      ["bb","cc","d"]
"adefaddaccc"                  ["e","f","ccc"]
"ababa"                        ["ababa"]
"abcaca"                       ["b"]
"aba"                          ["b"]
"abba"                         ["bb"]
"abcbac"                       ["abcbac"]
"abcbca"                       ["bcbc"]
"abcabca"                      ["abcabca"]
"abcacba"                      ["abcacba"]
"abca"                         ["b","c"]
"bcaba"                        ["c"]
"acbaba"                       ["c"]
"abcaba"                       ["c"]
)");

class t1520 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1520, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1520,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
