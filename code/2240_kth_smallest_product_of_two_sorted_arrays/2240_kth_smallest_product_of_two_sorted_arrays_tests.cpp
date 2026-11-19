#include "2240_kth_smallest_product_of_two_sorted_arrays.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>, u64>,
    i64>(R"cases(
[2,5] [3,4] 2 8
[-4,-2,0,3] [2,4] 6 0
)cases");

class t2240_kth_smallest_product_of_two_sorted_arrays
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2240_kth_smallest_product_of_two_sorted_arrays, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [a, b, k] = inputs;
    ASSERT_EQ(expected, Solution{}.kthSmallestProduct(a, b, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2240_kth_smallest_product_of_two_sorted_arrays,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
