#include "1922_count_good_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countGoodNumbers;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 5

4 400

50 564908303

806166225460393 643535977
)cases");

class t1922_count_good_numbers : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1922_count_good_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countGoodNumbers(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1922_count_good_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
