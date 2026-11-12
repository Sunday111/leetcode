#include "1306.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canReach;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,2,3,0,3,1,2]
5
true
[4,2,3,0,3,1,2]
0
true
[3,0,2,1,2]
2
false
)");

class t1306 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1306, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1306,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
