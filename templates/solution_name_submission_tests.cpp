#include "gtest/gtest.h"

// Exercise the judge branch in its own translation unit.
#undef LC_LOCAL_BUILD
#include "solution_name.hpp"

namespace
{
class LC_SOLUTION_NAME(ignored_suffix)
{
public:
    static int answer() { return 42; }
};

TEST(SolutionName, SubmissionUsesTheJudgeClassName)
{
    EXPECT_EQ(Solution{}.answer(), 42);
}
}  // namespace
