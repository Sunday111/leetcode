#include "3321_find_xsum_of_all_klong_subarrays_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int, unsigned int>,
    std::vector<long long>>(R"cases(
[1,1,2,2,3,4,2,3] 6 2 [6,10,12]
)cases");

class t3321_find_xsum_of_all_klong_subarrays_ii
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3321_find_xsum_of_all_klong_subarrays_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findXSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3321_find_xsum_of_all_klong_subarrays_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
