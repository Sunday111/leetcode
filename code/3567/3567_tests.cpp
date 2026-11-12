#include "3567.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minAbsDiff;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[20195,15337,73189,16963,-90840],[10664,-43796,-61984,13235,-33619]]
2
[[4673,18188,3728,3728]]


[[1,8],[3,-2]]
2
[[2]]

[[3,-1]]
1
[[0,0]]

[[1,-2,3],[2,3,5]]
2
[[1,2]]


)");

class t3567 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3567, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3567,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
