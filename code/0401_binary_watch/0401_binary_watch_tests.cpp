#include "0401_binary_watch.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::readBinaryWatch;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
)cases");

using t0401_binary_watch = SolutionTests<Solution>;

TEST_P(t0401_binary_watch, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.readBinaryWatch(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0401_binary_watch,
    t0401_binary_watch::parameters(kCases.size()),
    t0401_binary_watch::name);
