#include "1967.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numOfStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["a","abc","bc","d"] "abc"          3
["a","b","c"]        "aaaaabbbbb"   2
["a","a","a"]        "ab"           3
)");

class t1967 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1967, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1967,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
