#include "0242_valid_anagram.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAnagram;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"anagram" "nagaram" true

"rat" "car" false
)cases");

class t0242_valid_anagram : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0242_valid_anagram, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isAnagram(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0242_valid_anagram,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
