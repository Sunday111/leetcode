#include "0368_lexicographical_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lexicalOrder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
13 [1,10,11,12,13,2,3,4,5,6,7,8,9]
)cases");

class t0368_lexicographical_numbers : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0368_lexicographical_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.lexicalOrder(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0368_lexicographical_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
