#include "0797_all_paths_from_source_to_target.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::allPathsSourceTarget;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3],[3],[]] [[0,1,3],[0,2,3]]

[[4,3,1],[3,2,4],[3],[4],[]] [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
)cases");

class t0797_all_paths_from_source_to_target
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0797_all_paths_from_source_to_target, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.allPathsSourceTarget(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0797_all_paths_from_source_to_target,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
