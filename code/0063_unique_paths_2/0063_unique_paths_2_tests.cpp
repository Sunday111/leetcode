#include "0063_unique_paths_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::uniquePathsWithObstacles;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,0],[0,1,0],[0,0,0]] 2

[[0,1],[0,0]] 1

[[1,0]] 0
)cases");

class t0063_unique_paths_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0063_unique_paths_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.uniquePathsWithObstacles(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0063_unique_paths_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
