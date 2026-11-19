#include "3823_reverse_letters_then_special_characters_in_a_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseByType;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
")ebc#da@f(" "(fad@cb#e)"

"!@#$%^&*()" ")(*&^%$#@!"
)cases");

class t3823_reverse_letters_then_special_characters_in_a_string
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3823_reverse_letters_then_special_characters_in_a_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.reverseByType(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3823_reverse_letters_then_special_characters_in_a_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
