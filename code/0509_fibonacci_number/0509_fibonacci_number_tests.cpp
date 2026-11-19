#include "0509_fibonacci_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fib;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
0 0

1 1

2 1

3 2

4 3
)cases");

class t0509_fibonacci_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0509_fibonacci_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.fib(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0509_fibonacci_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
