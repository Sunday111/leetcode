#include "1653_Minimum_Deletions_to_Make_String_Balanced.hpp"
#include "gtest/gtest.h"

TEST(t1653_Minimum_Deletions_to_Make_String_Balanced, test_1)
{
    std::string s = "aababbab";
    ASSERT_EQ(Solution{}.minimumDeletions(s), 2);
}

TEST(t1653_Minimum_Deletions_to_Make_String_Balanced, test_2)
{
    std::string s = "bbaaaaabb";
    ASSERT_EQ(Solution{}.minimumDeletions(s), 2);
}
