#include "0241.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

inline static constexpr auto kMethodToTest = &Solution::diffWaysToCompute;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"2*3-4*5"   [-34,-14,-10,-10,10]
"2-1-1"     [0,2]
)");

class t0241 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0241, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    std::ranges::sort(actual);
    std::ranges::sort(expected);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0241,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
