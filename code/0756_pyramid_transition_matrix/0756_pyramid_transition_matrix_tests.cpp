#include "0756_pyramid_transition_matrix.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::pyramidTransition;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"BCD" ["BCC","CDE","CEA","FFF"] true

"AAAA" ["AAB","AAC","BCD","BBE","DEF"] false

"ABCD" ["ABC","BCA","CDA","ABD","BCE","CDF","DEA","EFF","AFF"] true
)cases");

class t0756_pyramid_transition_matrix : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0756_pyramid_transition_matrix, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.pyramidTransition(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0756_pyramid_transition_matrix,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
