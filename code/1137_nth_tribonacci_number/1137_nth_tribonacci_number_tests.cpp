#include "1137_nth_tribonacci_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::tribonacci;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 4

25 1389537
)cases");

class t1137_nth_tribonacci_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1137_nth_tribonacci_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.tribonacci(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1137_nth_tribonacci_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
