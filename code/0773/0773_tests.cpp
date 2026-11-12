#include "0773.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::slidingPuzzle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,0,5]]
1
[[1,2,3],[5,4,0]]
-1
[[4,1,2],[5,0,3]]
5
[[1,3,4],[0,2,5]]
14
[[3,2,4],[1,5,0]]
14
[[2,4,1],[5,3,0]]
12
[[0,5,2],[4,3,1]]
15
[[4,2,0],[5,1,3]]
7
[[3,0,1],[4,2,5]]
-1
[[3,2,1],[4,0,5]]
-1
[[1,2,3],[4,5,0]]
0
)");

class t0773 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0773, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0773,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
