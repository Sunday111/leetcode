#include "3418.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumAmount;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,-1],[1,-2,3],[2,-3,4]]
8

[[10,10,10],[10,10,10]]
40


)");

class t3418 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3418, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3418,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
