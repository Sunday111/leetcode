#include "0097_interleaving_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isInterleave;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aabcc" "dbbca" "aadbbcbcac" true

"aabcc" "dbbca" "aadbbbaccc" false

"ab" "bc" "babc" true
)cases");

class t0097_interleaving_string : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0097_interleaving_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isInterleave(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0097_interleaving_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
