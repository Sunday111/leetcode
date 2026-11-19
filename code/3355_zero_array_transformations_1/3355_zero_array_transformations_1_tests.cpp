#include "3355_zero_array_transformations_1.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isZeroArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,0,1] [[0,2]] true

[4,6] [[0,0],[0,0],[0,0],[0,0],[0,0],[0,1],[0,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1]] true

[0,3,9] [[0,2],[0,2],[1,1],[1,2],[1,2],[2,2]] false

[1,1,3] [[0,0],[0,0],[0,0],[0,1],[0,2],[0,2],[1,1],[1,1],[1,1],[1,1],[2,2],[2,2]] true
)cases");

class t3355_zero_array_transformations_1
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3355_zero_array_transformations_1, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isZeroArray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3355_zero_array_transformations_1,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
