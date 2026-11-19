#include "0218_the_skyline_problem.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getSkyline;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]] [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
)cases");

class t0218_the_skyline_problem : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0218_the_skyline_problem, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.getSkyline(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0218_the_skyline_problem,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
