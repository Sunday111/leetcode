#include "0065_valid_number.hpp"
#include "gtest/gtest.h"

// TEST(t0065_valid_number, test_1)
// {
//     ASSERT_TRUE(Solution{}.isNumber("0"));
// }

// TEST(t0065_valid_number, test_2)
// {
//     ASSERT_TRUE(Solution{}.isNumber("-1E+3"));
// }

// TEST(t0065_valid_number, test_3)
// {
//     ASSERT_FALSE(Solution{}.isNumber("e9"));
// }

TEST(t0065_valid_number, test_4)
{
    ASSERT_TRUE(Solution{}.isNumber("32.e-80123"));
}
