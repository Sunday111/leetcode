#include "1039_minimum_score_triangulation_of_polygon.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minScoreTriangulation;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,3,1,4,1,5] 13
)cases");

class t1039_minimum_score_triangulation_of_polygon
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1039_minimum_score_triangulation_of_polygon, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minScoreTriangulation(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1039_minimum_score_triangulation_of_polygon,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
