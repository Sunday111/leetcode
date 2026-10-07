#include <algorithm>

#include "0301_test_cases.hpp"
#include "gtest/gtest.h"

class t0301 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0301, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

TEST(t0301Reuse, MultipleCalls)
{
    Solution instance{};
    for (auto [inputs, expected] : kCases)
    {
        auto actual =
            std::apply(std::bind_front(kMethodToTest, &instance), inputs);
        std::ranges::sort(expected);
        std::ranges::sort(actual);
        ASSERT_EQ(expected, actual);
    }
}

TEST(t0301Input, Unchanged)
{
    std::string input = ")a)b(c(";
    auto actual = Solution{}.removeInvalidParentheses(input);
    EXPECT_EQ(input, ")a)b(c(");
    EXPECT_EQ(actual, (std::vector<std::string>{"abc"}));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0301,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
