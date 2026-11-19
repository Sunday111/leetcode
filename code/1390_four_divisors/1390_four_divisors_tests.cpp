#include "1390_four_divisors.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sumFourDivisors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[31911,85919,25557,9951,3936,88317,71321,74651,88416,34378] 289182
)cases");

class t1390_four_divisors : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1390_four_divisors, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.sumFourDivisors(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1390_four_divisors,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
