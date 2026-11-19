#include "1590_make_sum_divisible_by_p.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minSubarray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,1,4,2] 6 1
)cases");

class t1590_make_sum_divisible_by_p : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1590_make_sum_divisible_by_p, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minSubarray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1590_make_sum_divisible_by_p,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
