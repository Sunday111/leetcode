#include "3335_total_characters_in_string_after_transformations_1.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lengthAfterTransformations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcyy" 2 7

"azbk" 5 5
)cases");

class t3335_total_characters_in_string_after_transformations_1
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3335_total_characters_in_string_after_transformations_1, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.lengthAfterTransformations(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3335_total_characters_in_string_after_transformations_1,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
