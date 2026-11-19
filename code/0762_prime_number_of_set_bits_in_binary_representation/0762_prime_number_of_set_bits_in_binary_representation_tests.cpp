#include <immintrin.h>

#include <print>

#include "0762_prime_number_of_set_bits_in_binary_representation.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countPrimeSetBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
6 10 4

10 15 5

990000 1000000 3754
)cases");

class t0762_prime_number_of_set_bits_in_binary_representation
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0762_prime_number_of_set_bits_in_binary_representation, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countPrimeSetBits(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0762_prime_number_of_set_bits_in_binary_representation,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
