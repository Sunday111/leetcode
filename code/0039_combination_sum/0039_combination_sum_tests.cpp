#include <algorithm>

#include "0039_combination_sum.hpp"
#include "0039_combination_sum_2.hpp"
#include "0039_combination_sum_3.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::combinationSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,3,6,7] 7 [[2,2,3],[7]]

[38] 35 []
)");

class t0039_combination_sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0039_combination_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto check = [&]<typename Solver>()
    {
        auto values = inputs;
        auto actual = std::apply(
            [](auto&... args) { return Solver{}.combinationSum(args...); },
            values);
        ASSERT_EQ(sorted(expected), sorted(actual));
    };
    check.operator()<Solution>();
    check.operator()<Solution2>();
    check.operator()<Solution3>();
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0039_combination_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
