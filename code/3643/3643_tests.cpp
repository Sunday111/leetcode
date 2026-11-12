#include "3643.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::reverseSubmatrix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
1
0
3
[[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]

[[3,4,2,3],[2,3,4,2]]
0
2
2
[[3,4,4,2],[2,3,2,3]]


)");

class t3643 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3643, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3643,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
