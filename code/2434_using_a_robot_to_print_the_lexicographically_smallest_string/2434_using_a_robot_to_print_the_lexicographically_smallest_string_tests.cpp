#include "2434_using_a_robot_to_print_the_lexicographically_smallest_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::robotWithString;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"zza" "azz"

"bac" "abc"

"bdda" "addb"

"bydizfve" "bdevfziy"

"bzeyxf" "befxyz"

"vzhofnpo" "fnohopzv"

"mmuqezwmomeplrtskz" "eekstrlpmomwzqummz"
)cases");

class t2434_using_a_robot_to_print_the_lexicographically_smallest_string
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.robotWithString(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2434_using_a_robot_to_print_the_lexicographically_smallest_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
