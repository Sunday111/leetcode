#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

#include "1409_queries_on_a_permutation_with_key.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::processQueries;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,1,2,1] 5 [2,1,2,1]

[4,4,4,4] 4 [3,0,0,0]
)cases");

class t1409_queries_on_a_permutation_with_key
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1409_queries_on_a_permutation_with_key, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    const auto original = inputs;
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.processQueries(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(original, inputs);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1409_queries_on_a_permutation_with_key,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
