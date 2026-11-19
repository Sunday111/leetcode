#include "1249_minimum_remove_to_make_valid_parentheses.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minRemoveToMakeValid;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"lee(t(c)o)de)" "lee(t(c)o)de"

"a)b(c)d" "ab(c)d"

"))((" ""

"(a(b(c)d)" "a(b(c)d)"
)cases");

class t1249_minimum_remove_to_make_valid_parentheses
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1249_minimum_remove_to_make_valid_parentheses, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minRemoveToMakeValid(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1249_minimum_remove_to_make_valid_parentheses,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
