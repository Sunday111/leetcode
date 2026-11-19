#include "0560_subarray_sum_equals_k.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::subarraySum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1] 2 2

[1,2,3] 3 2
)cases");

class t0560_subarray_sum_equals_k : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0560_subarray_sum_equals_k, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.subarraySum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0560_subarray_sum_equals_k,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
