#include "1006_clumsy_factorial.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::clumsy;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 7

10 12
)cases");

class t1006_clumsy_factorial : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1006_clumsy_factorial, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.clumsy(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1006_clumsy_factorial,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
