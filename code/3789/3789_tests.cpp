#include "3789.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
2
1
3
2
3

5
4
15
2
3
22

5
4
15
0
0
0


)");

class t3789 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3789, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3789,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
