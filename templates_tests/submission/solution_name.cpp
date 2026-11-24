#include "gtest/gtest.h"

// Exercise the judge branch in its own translation unit.
#undef LC_LOCAL_BUILD
#include "solution_name.hpp"

namespace
{
class LC_SOLUTION_NAME(_ignored_suffix)
{
public:
    static int answer() { return 42; }
};

TEST(SolutionName, SubmissionUsesTheJudgeClassName)
{
    EXPECT_EQ(Solution{}.answer(), 42);
}
namespace default_solution
{
class LC_SOLUTION_NAME()
{
public:
    static int answer() { return 7; }
};
}  // namespace default_solution

TEST(SolutionName, SubmissionAcceptsEmptySuffix)
{
    EXPECT_EQ(default_solution::Solution::answer(), 7);
}
}  // namespace
