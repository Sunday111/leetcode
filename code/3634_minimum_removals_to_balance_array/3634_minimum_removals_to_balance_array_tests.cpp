#include "3634_minimum_removals_to_balance_array.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int>,
    unsigned int>(R"cases(
[2,1,5] 2 1

[1,6,2,9] 3 2

[4,6] 2 0

[1,34,23] 2 1
)cases");

class t3634_minimum_removals_to_balance_array
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3634_minimum_removals_to_balance_array, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minRemoval(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3634_minimum_removals_to_balance_array,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
