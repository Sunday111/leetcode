#include "0204_count_primes.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countPrimes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 4

0 0

1 0

5000000 348513
)cases");

class t0204_count_primes : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0204_count_primes, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countPrimes(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0204_count_primes,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
