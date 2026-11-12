#include "2812.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumSafenessFactor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,0,0],[0,0,0],[0,0,1]]                       0
[[0,0,1],[0,0,0],[0,0,0]]                       2
[[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]       2
)");

class t2812 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2812, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2812,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
