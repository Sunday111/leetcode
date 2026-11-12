#include <tuple>
#include <vector>

#include "3693.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::climbStairs;
inline static const auto kCases = []
{
    auto cases = parse_test_cases<kMethodToTest>(R"(
4
[1,2,3,4]
13

4
[5,1,6,2]
11

3
[9,8,3]
12

1
[1]
2

1
[10000]
10001

2
[1,10000]
10003

2
[10000,1]
5

5
[1,10000,1,10000,1]
12

6
[10000,10000,10000,10000,10000,10000]
20018

7
[10000,10000,10000,10000,10000,10000,10000]
30017

8
[10000,10000,10000,10000,10000,10000,10000,10000]
30022
)");
    cases.emplace_back(
        std::tuple{100'000u, std::vector<int>(100'000, 1)},
        200'000u);
    cases.emplace_back(
        std::tuple{100'000u, std::vector<int>(100'000, 10'000)},
        333'639'996u);
    return cases;
}();

class t3693 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3693, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3693,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
