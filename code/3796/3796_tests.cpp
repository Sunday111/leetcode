#include "3796.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMaxVal;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[[3,1],[8,1]]
[2,2,3,1,4,5,1,1,2]
6

8
[[3,2]]
[3,5,2,4,2,3,1]
12


)");

class t3796 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3796, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3796,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
