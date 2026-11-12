#include "2492.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
5

4
[[1,2,2],[1,3,4],[3,4,7]]
2

7
[[1,3,1484],[3,2,3876],[2,4,6823],[6,7,579],[5,6,4436],[4,5,8830]]
579

13
[[2,12,1891],[10,9,4138],[11,3,2007],[1,10,9390],[12,8,1915],[6,2,1098],[5,4,2795],[3,13,4562],[9,7,9202],[4,6,6752],[8,11,1480],[7,5,9827]]
1098

)");

class t2492 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2492, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2492,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
