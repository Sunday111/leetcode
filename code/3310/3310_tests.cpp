#include "3310.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::remainingMethods;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
1
[[1,2],[0,1],[3,2]]
[0,1,2,3]

5
0
[[1,2],[0,2],[0,1],[3,4]]
[3,4]

3
2
[[1,2],[0,1],[2,0]]
[]

4
0
[[2,3],[1,2]]
[1,2,3]

3
2
[[1,0],[2,0]]
[0,1,2]
)");

class t3310 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3310, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3310,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
