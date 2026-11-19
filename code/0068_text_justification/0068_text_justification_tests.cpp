#include "0068_text_justification.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fullJustify;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["This","is","an","example","of","text","justification."]
16
["This    is    an","example  of text","justification.  "]
)cases");

class t0068_text_justification : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0068_text_justification, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.fullJustify(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0068_text_justification,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
