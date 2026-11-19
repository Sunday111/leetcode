#include "3337_total_characters_in_string_after_transformations_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lengthAfterTransformations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcyy" 2 [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2] 7

"azbk" 1 [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2] 8

"abcyrsmtfyjhnvhvrtmhvvngvmkempcvepbgxxbeebyhy"
999
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
869688536
)cases");

class t3337_total_characters_in_string_after_transformations_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3337_total_characters_in_string_after_transformations_2, Test)
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
    t3337_total_characters_in_string_after_transformations_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
