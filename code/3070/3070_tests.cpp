#include "3070.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countSubmatrices;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[7,6,3],[6,6,1]]
18
4

[[7,2,9],[1,5,0],[2,6,6]]
20
6

[
 [1,10],
 [7,2],
 [9,1],
 [4,1]
]
8
2
)");

class t3070 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3070, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3070,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
