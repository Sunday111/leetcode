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

TEST(t0756_pyramid_transition_matrix, test_5)
{
    std::string bottom = "AFFFFA";
    std::vector<std::string> allowed{
        "ADA", "ADC", "ADB", "AEA", "AEC", "AEB", "AFA", "AFC", "AFB", "CDA",
        "CDC", "CDB", "CEA", "CEC", "CEB", "CFA", "CFC", "CFB", "BDA", "BDC",
        "BDB", "BEA", "BEC", "BEB", "BFA", "BFC", "BFB", "DAA", "DAC", "DAB",
        "DCA", "DCC", "DCB", "DBA", "DBC", "DBB", "EAA", "EAC", "EAB", "ECA",
        "ECC", "ECB", "EBA", "EBC", "EBB", "FAA", "FAC", "FAB", "FCA", "FCC",
        "FCB", "FBA", "FBC", "FBB", "DDA", "DDC", "DDB", "DEA", "DEC", "DEB",
        "DFA", "DFC", "DFB", "EDA", "EDC", "EDB", "EEA", "EEC", "EEB", "EFA",
        "EFC", "EFB", "FDA", "FDC", "FDB", "FEA", "FEC", "FEB", "FFA", "FFC",
        "FFB", "DDD", "DDE", "DDF", "DED", "DEE", "DEF", "DFD", "DFE", "DFF",
        "EDD", "EDE", "EDF", "EED", "EEE", "EEF", "EFD", "EFE", "EFF", "FDD",
        "FDE", "FDF", "FED", "FEE", "FEF", "FFD", "FFE", "FFF"};
    ASSERT_EQ(Solution{}.pyramidTransition(bottom, allowed), true);
}
