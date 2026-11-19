#include "____problem_name____.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::____method_name____;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
____test_data____
)");

using t____problem_name____ = SolutionTests<Solution>;

TEST_P(t____problem_name____, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.____method_name____(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t____problem_name____,
    t____problem_name____::parameters(kCases.size()),
    t____problem_name____::name);
