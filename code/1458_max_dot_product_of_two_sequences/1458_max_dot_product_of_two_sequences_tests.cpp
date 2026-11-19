#include "1458_max_dot_product_of_two_sequences.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxDotProduct;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,1,-2,5] [3,0,-6] 18

[3,-2] [2,-6,7] 21

[-1,-1] [1,1] -1

[-3,-8,3,-10,1,3] [9,2,3,7,-9,1,5] 133

[-3,-8,3,-10,1,3,9] [9,2,3,7,-9,1,-8,5,-1,-1] 200

[-3,-8,-10] [7,-9,-8] 152
)cases");

class t1458_max_dot_product_of_two_sequences
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1458_max_dot_product_of_two_sequences, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxDotProduct(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1458_max_dot_product_of_two_sequences,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
