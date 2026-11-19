#include "1653_Minimum_Deletions_to_Make_String_Balanced.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeletions;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aababbab" 2

"bbaaaaabb" 2
)cases");

class t1653_Minimum_Deletions_to_Make_String_Balanced
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1653_Minimum_Deletions_to_Make_String_Balanced, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumDeletions(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1653_Minimum_Deletions_to_Make_String_Balanced,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
