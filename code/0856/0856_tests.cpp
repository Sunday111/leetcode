#include "0856.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::scoreOfParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()" 1
"(())" 2
"()()" 2
"(()(()))" 6
"((()))" 4
"(()())" 4
"(())()" 3
"()(())" 3
"(()())(())" 6
"((())())" 6
"((()()))" 8
"()()()()()()()()()()()()()()()()()()()()()()()()()" 25
"((((((((((((((((((((((((()))))))))))))))))))))))))" 16777216
)cases");

class t0856 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0856, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0856,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
