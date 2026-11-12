#include "1402.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSatisfaction;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,-8,0,5,-7]
14
[4,3,2]
20
[-1,-4,-5]
0
)");

class t1402 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1402, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1402,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
