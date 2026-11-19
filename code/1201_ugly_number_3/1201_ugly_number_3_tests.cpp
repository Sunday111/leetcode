#include "1201_ugly_number_3.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 2 3 5 4

4 2 3 4 6

5 2 11 13 10

1000000000 2 740091218 473796308 2000000000
)cases");

class t1201_ugly_number_3 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1201_ugly_number_3, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.nthUglyNumber(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1201_ugly_number_3,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
