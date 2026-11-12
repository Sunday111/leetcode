#include "2087.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,0]
[2,3]
[5,4,3]
[8,2,6,7]
18

[0,0]
[0,0]
[5]
[26]
0
)");

class t2087 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2087, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2087,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
