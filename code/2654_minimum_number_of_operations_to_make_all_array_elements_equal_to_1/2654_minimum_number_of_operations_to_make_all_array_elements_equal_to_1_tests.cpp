#include "2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[6,10,15] 4

[2,6,3,4] 4
)cases");

class t2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(
    t2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1,
    Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minOperations(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
