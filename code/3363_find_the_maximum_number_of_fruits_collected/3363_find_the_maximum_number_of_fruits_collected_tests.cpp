#include "3363_find_the_maximum_number_of_fruits_collected.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxCollectedFruits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]] 100
)cases");

class t3363_find_the_maximum_number_of_fruits_collected
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3363_find_the_maximum_number_of_fruits_collected, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxCollectedFruits(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3363_find_the_maximum_number_of_fruits_collected,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
