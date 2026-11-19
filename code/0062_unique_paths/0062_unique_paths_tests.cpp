#include "0062_unique_paths.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::uniquePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 7 28

3 2 3
)cases");

class t0062_unique_paths : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0062_unique_paths, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.uniquePaths(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0062_unique_paths,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
