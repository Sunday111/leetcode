#include "1074.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numSubmatrixSumTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,0],[1,1,1],[0,1,0]]
0
4

[[1,-1],[-1,1]]
0
5

[[904]]
0
0
)");

class t1074 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1074, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1074,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
