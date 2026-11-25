#include "3934.hpp"
#include "3934_flat.hpp"
#include "3934_golf.hpp"
#include "3934_golf_bounds.hpp"
#include "3934_hash_table.hpp"
#include "3934_table_size.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestUniqueSubarray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,3,3]
3

[2,1,2,3,3]
1

[1,1,2,2,1]
2


)");

using t3934 = SolutionTests<
    Solution,
    Solution_hash_table,
    Solution_table_size,
    Solution_flat,
    Solution_golf,
    Solution_golf_bounds>;

TEST_P(t3934, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestUniqueSubarray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3934,
    t3934::parameters(kCases.size()),
    t3934::name);
