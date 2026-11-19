#include "0953_verifying_an_alien_dictionary.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAlienSorted;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["hello","leetcode"] "hlabcdefgijkmnopqrstuvwxyz" true
)cases");

class t0953_verifying_an_alien_dictionary
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0953_verifying_an_alien_dictionary, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isAlienSorted(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0953_verifying_an_alien_dictionary,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
