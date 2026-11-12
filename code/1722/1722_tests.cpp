#include "1722.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumHammingDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4]
[2,1,4,5]
[[0,1],[2,3]]
1

[1,2,3,4]
[1,3,2,4]
[]
2

[5,1,2,4,3]
[1,5,4,2,3]
[[0,4],[4,2],[1,3],[1,4]]
0
)");

class t1722 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1722, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1722,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
