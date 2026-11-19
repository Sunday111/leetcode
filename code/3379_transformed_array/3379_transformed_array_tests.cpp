#include "3379_transformed_array.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::constructTransformedArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,-2,1,1] [1,1,1,3]
)cases");

class t3379_transformed_array : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3379_transformed_array, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.constructTransformedArray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3379_transformed_array,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
