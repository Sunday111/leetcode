#include "3186_maximum_total_damage_with_spell_casting.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumTotalDamage;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[7,1,6,6] 13

[3,4,5,6,6,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,6] 104
)cases");

using t3186_maximum_total_damage_with_spell_casting = SolutionTests<Solution>;

TEST_P(t3186_maximum_total_damage_with_spell_casting, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumTotalDamage(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3186_maximum_total_damage_with_spell_casting,
    t3186_maximum_total_damage_with_spell_casting::parameters(kCases.size()),
    t3186_maximum_total_damage_with_spell_casting::name);
