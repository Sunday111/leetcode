#include "1840.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxBuilding;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
5
[[2,1],[4,1]]
2

6
[]
5

10
[[5,3],[2,5],[7,4],[10,3]]
5

10
[[8,5],[9,0],[6,2],[4,0],[3,2],[10,0],[5,3],[7,3],[2,4]]
2
)");

class t1840 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1840, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1840,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
