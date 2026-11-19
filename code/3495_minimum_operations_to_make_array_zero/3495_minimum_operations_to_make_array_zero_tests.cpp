#include "3495_minimum_operations_to_make_array_zero.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[2,4]] 3
)cases");

class t3495_minimum_operations_to_make_array_zero
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3495_minimum_operations_to_make_array_zero, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minOperations(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3495_minimum_operations_to_make_array_zero,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
