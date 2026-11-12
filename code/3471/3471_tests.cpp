#include "3471.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,9,2,1,7]
3
7

[3,9,7,2,1,7]
4
3

[0,0]
1
-1


)");

class t3471 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3471, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3471,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
