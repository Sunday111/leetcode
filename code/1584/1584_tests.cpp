#include "1584.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCostConnectPoints;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0],[2,2],[3,10],[5,2],[7,0]]    20
[[3,12],[-2,5],[-4,1]]              18
[[2,-3],[-17,-8],[13,8],[-17,-15]]  53
[[0,0]]                             0
)");

class t1584 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1584, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1584,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
