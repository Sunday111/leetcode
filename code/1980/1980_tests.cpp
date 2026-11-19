#include <algorithm>

#include "1980.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<std::string>>, size_t>(
        R"(
["01","10"] 2
["00","01"] 2
["111","011","001"] 3
["0"] 1
["1"] 1
)");

using t1980 = SolutionTests<Solution>;

TEST_P(t1980, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, size_t expected_length)
        {
            auto& [nums] = inputs;
            const auto original = nums;
            auto actual = solution.findDifferentBinaryString(nums);
            ASSERT_EQ(actual.size(), expected_length);
            EXPECT_TRUE(
                std::ranges::all_of(
                    actual,
                    [](char c) { return c == '0' || c == '1'; }));
            EXPECT_EQ(std::ranges::find(original, actual), original.end());
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1980,
    t1980::parameters(kCases.size()),
    t1980::name);
