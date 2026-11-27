#include "3947.hpp"
#include "3947_2.hpp"
#include "3947_3.hpp"
#include "3947_4.hpp"
#include "3947_5.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumSaleItems;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,100],[3,100],[4,199],[6,199],[5,199],[5,199]]
300
6

[[1,4],[2,3]]
13
5

[[1,6],[2,4],[3,5]]
19
5

[[2,8],[1,10],[6,6],[4,12],[5,20],[5,17]]
35
7


)");

using t3947 =
    SolutionTests<Solution, Solution_2, Solution_3, Solution_4, Solution_5>;

TEST_P(t3947, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumSaleItems(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3947,
    t3947::parameters(kCases.size()),
    t3947::name);
