#include "0016_3sum_closest.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::threeSumClosest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,2,1,-4] 1 2

[0,0,0] 1 0

[1,5,6,7,8] 10 12

[2,3,8,9,10] 16 15

[-1000,-5,-5,-5,-1] -14 -15

[-2,-1,1,4] 0 1

[0,1,2] 3 3

[0,3,97,102,200] 300 300
)");

class t0016_3sum_closest : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0016_3sum_closest, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.threeSumClosest(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0016_3sum_closest,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
