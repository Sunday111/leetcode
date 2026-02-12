#include "0756_pyramid_transition_matrix.hpp"
#include "gtest/gtest.h"

TEST(t0756_pyramid_transition_matrix, test_1)
{
    std::string bottom = "BCD";
    std::vector<std::string> allowed{"BCC", "CDE", "CEA", "FFF"};
    ASSERT_EQ(Solution{}.pyramidTransition(bottom, allowed), true);
}

TEST(t0756_pyramid_transition_matrix, test_2)
{
    std::string bottom = "AAAA";
    std::vector<std::string> allowed{"AAB", "AAC", "BCD", "BBE", "DEF"};
    ASSERT_EQ(Solution{}.pyramidTransition(bottom, allowed), false);
}

TEST(t0756_pyramid_transition_matrix, test_3)
{
    std::string bottom = "ABCD";
    std::vector<std::string>
        allowed{"ABC", "BCA", "CDA", "ABD", "BCE", "CDF", "DEA", "EFF", "AFF"};
    ASSERT_EQ(Solution{}.pyramidTransition(bottom, allowed), true);
}

TEST(t0756_pyramid_transition_matrix, test_4)
{
    std::string bottom = "CBDDA";
    std::vector<std::string> allowed{
        "ACC", "ACA", "AAB", "BCA", "BCB", "BAC", "BAA", "CAC", "BDA",
        "CAA", "CCA", "CCC", "CCB", "DAD", "CCD", "DAB", "ACD", "DCA",
        "CAD", "CBB", "ABB", "ABC", "ABD", "BDB", "BBC", "BBA", "DDA",
        "CDD", "CBC", "CBA", "CDA", "DBA", "ABA"};
    ASSERT_EQ(Solution{}.pyramidTransition(bottom, allowed), true);
}
