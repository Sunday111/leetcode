#include "3882.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2],[3,4]]
6

[[6,7],[5,8]]
9

[[2,7,5]]
0

[[1023]]
1023

[[1],[2],[4],[8]]
15

[[0,0,0],[0,0,0]]
0

[[1023,1023],[1023,1023]]
1023

[[31,32],[63,64]]
96

[[64,128],[256,512]]
704

[[1,3],[2,3]]
0

)");

class t3882 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3882, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3882,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
