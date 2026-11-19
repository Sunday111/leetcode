#include "1913_maximum_product_difference_between_two_pairs.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, unsigned int>(
        R"cases(
[5,6,2,7,4] 34
)cases");

class t1913_maximum_product_difference_between_two_pairs
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1913_maximum_product_difference_between_two_pairs, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxProductDifference(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1913_maximum_product_difference_between_two_pairs,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
