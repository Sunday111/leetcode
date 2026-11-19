#include "2977_minimum_cost_to_convert_string_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumCost;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcdefgh" "acdeeghh" ["bcd","fgh","thh"] ["cde","thh","ghh"] [1,3,5] 9
)cases");

class t2977_minimum_cost_to_convert_string_ii
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2977_minimum_cost_to_convert_string_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumCost(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2977_minimum_cost_to_convert_string_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
