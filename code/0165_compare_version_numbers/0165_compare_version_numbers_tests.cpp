#include "0165_compare_version_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::compareVersion;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1.2" "1.10" -1

"1.0.1" "1" 1
)cases");

class t0165_compare_version_numbers : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0165_compare_version_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.compareVersion(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0165_compare_version_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
