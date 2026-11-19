#include <algorithm>
#include <print>

#include "0440_kth_smallest_in_lexicographical_order.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint64_t, uint64_t>, uint64_t>(
        R"cases(
13 2 10
1 1 1
100 10 17
)cases");

class t0440_kth_smallest_in_lexicographical_order
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0440_kth_smallest_in_lexicographical_order, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto [n, k] = inputs;
    ASSERT_EQ(expected, Solution{}.findKthNumber(n, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0440_kth_smallest_in_lexicographical_order,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
