#include "0950_reveal_cards_in_increasing_order.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::deckRevealedIncreasing;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[17,13,11,2,3,5,7] [2,13,3,11,5,17,7]
)cases");

class t0950_reveal_cards_in_increasing_order
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0950_reveal_cards_in_increasing_order, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.deckRevealedIncreasing(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0950_reveal_cards_in_increasing_order,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
