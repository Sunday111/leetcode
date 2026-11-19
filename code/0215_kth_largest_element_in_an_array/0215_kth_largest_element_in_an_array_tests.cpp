#include "0215_kth_largest_element_in_an_array.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findKthLargest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,5,9999] 1 9999
)cases");

class t0215_kth_largest_element_in_an_array
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0215_kth_largest_element_in_an_array, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findKthLargest(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0215_kth_largest_element_in_an_array,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
