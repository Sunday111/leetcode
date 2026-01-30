#include "2977_minimum_cost_to_convert_string_ii.hpp"
#include "gtest/gtest.h"

// TEST(t2977_minimum_cost_to_convert_string_ii, test_1)
// {
//     std::string_view source = "jegbx";
//     std::string_view target = "ezhfc";
//     std::vector<std::string> original{
//         "egbx", "hrbf", "twne", "snjd", "ysrf", "qzqg", "rcll", "ekvz",
//         "inpr", "frxs", "xcww", "unsw", "vdug", "ycvs", "j",    "v",    "j",
//         "y", "n",    "q",    "w",    "a",    "z",    "g",    "b",    "d"},
//         changed{"hrbf", "twne", "snjd", "ysrf", "qzqg", "rcll", "ekvz",
//                 "inpr", "frxs", "xcww", "unsw", "vdug", "ycvs", "zhfc",
//                 "v",    "j",    "y",    "n",    "q",    "w",    "a",
//                 "z",    "g",    "b",    "d",    "e"};
//     std::vector<int> cost{50682, 89150, 91153,  85032, 97960, 96862, 81138,
//                           86570, 77628, 45200,  44955, 70845, 99254, 80325,
//                           91331, 95349, 84374,  94177, 53994, 94284, 79531,
//                           92353, 60384, 100000, 93152, 19787};

//     i64 expected = 1868790;
//     ASSERT_EQ(
//         Solution{}.minimumCost(source, target, original, changed, cost),
//         expected);
// }
TEST(t2977_minimum_cost_to_convert_string_ii, test_2)
{
    std::string_view source = "abcdefgh";
    std::string_view target = "acdeeghh";
    std::vector<std::string> original{"bcd", "fgh", "thh"},
        changed{"cde", "thh", "ghh"};
    std::vector<int> cost{1, 3, 5};

    i64 expected = 9;
    ASSERT_EQ(
        Solution{}.minimumCost(source, target, original, changed, cost),
        expected);
}
