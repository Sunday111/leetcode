#include "2561_rearranging_fruits.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>>,
    long>(R"cases(
[4,2,2,2] [1,4,1,2] 1
)cases");

class t2561_rearranging_fruits : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2561_rearranging_fruits, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minCost(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2561_rearranging_fruits,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
