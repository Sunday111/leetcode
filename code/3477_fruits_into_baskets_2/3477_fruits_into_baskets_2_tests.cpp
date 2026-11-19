#include "3477_fruits_into_baskets_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numOfUnplacedFruits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,6,1] [6,4,7] 0
)cases");

class t3477_fruits_into_baskets_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3477_fruits_into_baskets_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numOfUnplacedFruits(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3477_fruits_into_baskets_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
