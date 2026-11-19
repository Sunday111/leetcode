#include "0313_super_ugly_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthSuperUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 [2,3,5] 12

1690 [2,3,5] 2123366400
)cases");

class t0313_super_ugly_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0313_super_ugly_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.nthSuperUglyNumber(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0313_super_ugly_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
