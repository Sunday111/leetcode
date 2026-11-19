#include "0263_ugly_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isUgly;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
0 false

1 true

6 true

14 false
)cases");

class t0263_ugly_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0263_ugly_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isUgly(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0263_ugly_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
