#include "3271_hash_divided_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::stringHash;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bf"

"mxz" 3 "i"

"hcr" 3 "a"
)cases");

class t3271_hash_divided_string : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3271_hash_divided_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.stringHash(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3271_hash_divided_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
