#include "3583_count_special_triplets.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::specialTriplets;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[6,3,6] 1

[0,1,0,0] 1
)cases");

using t3583_count_special_triplets = SolutionTests<Solution>;

TEST_P(t3583_count_special_triplets, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.specialTriplets(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3583_count_special_triplets,
    t3583_count_special_triplets::parameters(kCases.size()),
    t3583_count_special_triplets::name);
