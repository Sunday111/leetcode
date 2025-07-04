#include "2240_kth_smallest_product_of_two_sorted_arrays.hpp"
#include "gtest/gtest.h"

auto print_prods(auto& nums1, auto& nums2)
{
    std::vector<i64> prods;
    for (int a : nums1)
    {
        for (int b : nums2)
        {
            prods.push_back(i64{a} * i64{b});
        }
    }
    std::ranges::sort(prods);
    std::println("prods: {}", prods);
}

TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_1)
{
    // 6 8 15 20
    std::vector nums1{2, 5};
    std::vector nums2{3, 4};
    constexpr u64 k = 2;
    constexpr i64 expected = 8;
    ASSERT_EQ(Solution{}.kthSmallestProduct(nums1, nums2, k), expected);
}

TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_2)
{
    std::vector nums1{-4, -2, 0, 3};
    std::vector nums2{2, 4};

    constexpr u64 k = 6;
    constexpr i64 expected = 0;

    print_prods(nums1, nums2);
    ASSERT_EQ(Solution{}.kthSmallestProduct(nums1, nums2, k), expected);
}

TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_3)
{
    std::vector nums1{
        -498, -498, -498, -494, -494, -491, -489, -480, -478, -478, -475, -475,
        -472, -471, -469, -467, -464, -464, -461, -461, -461, -459, -458, -453,
        -449, -449, -442, -441, -440, -440, -439, -433, -432, -430, -430, -430,
        -430, -429, -426, -426, -425, -422, -420, -416, -412, -410, -407, -406,
        -405, -405, -404, -404, -403, -402, -398, -397, -397, -397, -393, -391,
        -389, -387, -383, -380, -380, -379, -377, -377, -376, -375, -374, -368,
        -367, -367, -367, -367, -367, -366, -364, -362, -362, -361, -359, -358,
        -356, -356, -353, -352, -352, -351, -349, -348, -348, -346, -345, -344,
        -344, -343, -336, -336, -334, -333, -332, -330, -329, -329, -326, -320,
        -319, -318, -318, -316, -314, -313, -313, -312, -312, -311, -311, -310,
        -310, -310, -309, -305, -303, -303, -303, -303, -298, -296, -296, -295,
        -292, -289, -288, -287, -287, -287, -286, -281, -281, -280, -278, -276,
        -274, -271, -271, -271, -269, -267, -267, -265, -262, -261, -260, -258,
        -257, -255, -253, -252, -252, -247, -247, -243, -241, -241, -239, -239,
        -238, -237, -236, -234, -233, -226, -224, -224, -223, -221, -221, -220,
        -220, -219, -219, -218, -218, -216, -216, -216, -211, -209, -208, -208,
        -207, -205, -203, -203, -200, -199, -199, -198, -197, -196, -196, -194,
        -193, -188, -186, -185, -185, -184, -184, -183, -183, -182, -179, -178,
        -177, -176, -175, -174, -172, -171, -171, -171, -170, -169, -169, -168,
        -167, -166, -165, -163, -163, -162, -161, -161, -161, -156, -154, -152,
        -152, -149, -149, -148, -148, -144, -143, -142, -142, -141, -140, -139,
        -139, -138, -137, -137, -136, -134, -133, -132, -132, -132, -130, -130,
        -129, -128, -126, -125, -121, -121, -120, -117, -117, -114, -114, -111,
        -110, -109, -109, -108, -104, -103, -102, -100, -100, -99,  -95,  -90,
        -90,  -90,  -88,  -88,  -87,  -84,  -83,  -82,  -81,  -79,  -79,  -77,
        -76,  -76,  -72,  -71,  -68,  -66,  -64,  -63,  -62,  -62,  -62,  -60,
        -60,  -60,  -57,  -56,  -54,  -53,  -53,  -53,  -53,  -52,  -52,  -49,
        -49,  -47,  -46,  -45,  -45,  -45,  -44,  -43,  -42,  -39,  -39,  -38,
        -37,  -36,  -35,  -35,  -34,  -34,  -34,  -30,  -30,  -30,  -29,  -27,
        -26,  -24,  -24,  -23,  -20,  -20,  -18,  -16,  -14,  -14,  -12,  -12,
        -12,  -12,  -12,  -11,  -9,   -8,   -7,   -6,   -4,   -2,   -1,   0,
        0,    3,    3,    4,    7,    7,    8,    10,   11,   16,   16,   16,
        16,   17,   17,   17,   20,   20,   20,   21,   25,   27,   28,   31,
        31,   35,   35,   36,   39,   41,   44,   46,   48,   48,   49,   49,
        50,   51,   52,   55,   56,   58,   60,   61,   61,   64,   65,   66,
        66,   67,   70,   74,   74,   74,   75,   77,   81,   86,   87,   88,
        88,   89,   90,   92,   93,   94,   95,   98,   99,   99,   100,  101,
        102,  103,  104,  105,  109,  109,  110,  110,  112,  115,  116,  116,
        117,  118,  119,  119,  121,  121,  121,  124,  126,  128,  130,  130,
        133,  133,  134,  136,  137,  139,  140,  141,  142,  142,  143,  144,
        144,  145,  145,  145,  146,  146,  149,  152,  154,  155,  155,  156,
        157,  158,  158,  160,  160,  161,  161,  162,  163,  165,  166,  167,
        169,  170,  174,  179,  179,  182,  185,  187,  188,  189,  190,  191,
        191,  195,  196,  200,  201,  202,  202,  204,  212,  212,  217,  218,
        220,  220,  224,  224,  226,  227,  227,  233,  234,  234,  234,  235,
        236,  236,  237,  239,  239,  241,  245,  246,  246,  246,  248,  249,
        250,  251,  252,  258,  263,  264,  265,  267,  268,  268,  268,  269,
        269,  269,  270,  273,  275,  282,  284,  288,  290,  291,  291,  293,
        295,  296,  299,  301,  302,  303,  304,  304,  305,  306,  307,  309,
        310,  310,  310,  311,  314,  316,  317,  317,  320,  321,  323,  323,
        323,  324,  325,  327,  328,  334,  334,  335,  336,  337,  340,  341,
        343,  344,  346,  347,  348,  348,  348,  349,  355,  356,  356,  358,
        358,  359,  360,  361,  362,  364,  364,  365,  365,  365,  365,  367,
        369,  369,  374,  376,  377,  378,  382,  383,  385,  389,  391,  392,
        394,  394,  394,  397,  399,  399,  400,  401,  401,  402,  402,  403,
        405,  408,  409,  412,  412,  413,  413,  414,  415,  415,  417,  417,
        420,  421,  422,  424,  424,  426,  433,  433,  433,  435,  436,  439,
        440,  442,  444,  445,  445,  449,  450,  451,  454,  454,  455,  456,
        456,  456,  456,  459,  460,  464,  464,  464,  464,  467,  469,  471,
        473,  473,  475,  478,  479,  479,  482,  482,  483,  483,  485,  491,
        491,  491,  496,  497,  500};
    std::vector nums2{
        -498, -498, -495, -494, -492, -490, -490, -490, -488, -488, -485, -485,
        -484, -484, -484, -484, -483, -482, -480, -477, -476, -471, -470, -467,
        -465, -464, -461, -461, -460, -460, -459, -457, -456, -455, -454, -453,
        -453, -452, -452, -449, -447, -446, -445, -445, -442, -441, -439, -438,
        -437, -437, -437, -435, -435, -431, -430, -429, -427, -426, -426, -426,
        -424, -422, -419, -417, -417, -415, -415, -415, -414, -413, -413, -410,
        -410, -408, -408, -408, -407, -406, -405, -401, -398, -397, -391, -391,
        -389, -389, -388, -387, -385, -384, -383, -381, -380, -378, -378, -376,
        -376, -375, -374, -374, -372, -371, -370, -369, -366, -364, -358, -357,
        -356, -356, -355, -354, -353, -353, -352, -350, -350, -350, -348, -347,
        -345, -344, -344, -343, -342, -341, -341, -340, -340, -339, -339, -336,
        -336, -336, -334, -332, -325, -324, -323, -323, -322, -322, -320, -320,
        -318, -317, -317, -315, -314, -313, -312, -312, -311, -311, -309, -309,
        -308, -306, -305, -305, -301, -300, -300, -298, -297, -294, -293, -293,
        -292, -292, -291, -289, -289, -288, -286, -284, -283, -281, -281, -281,
        -280, -276, -276, -271, -270, -269, -268, -266, -265, -264, -263, -262,
        -262, -262, -261, -261, -259, -255, -254, -254, -252, -249, -249, -247,
        -247, -246, -244, -243, -243, -242, -241, -239, -239, -239, -238, -236,
        -233, -233, -232, -231, -228, -226, -226, -225, -225, -224, -223, -221,
        -221, -220, -219, -217, -217, -216, -215, -213, -209, -209, -208, -207,
        -207, -206, -206, -204, -204, -203, -203, -203, -202, -201, -201, -198,
        -198, -198, -198, -196, -196, -195, -194, -193, -192, -192, -192, -191,
        -190, -189, -189, -189, -188, -187, -187, -186, -186, -184, -183, -183,
        -183, -183, -182, -181, -180, -178, -178, -177, -174, -172, -171, -171,
        -171, -169, -166, -165, -164, -164, -161, -161, -160, -158, -156, -156,
        -151, -150, -149, -149, -147, -146, -145, -144, -144, -139, -139, -138,
        -135, -135, -134, -133, -132, -132, -131, -131, -130, -127, -127, -127,
        -124, -124, -123, -121, -121, -120, -119, -117, -117, -117, -115, -113,
        -112, -111, -111, -111, -110, -108, -108, -103, -103, -101, -98,  -98,
        -98,  -98,  -97,  -96,  -96,  -95,  -95,  -95,  -93,  -93,  -92,  -91,
        -90,  -88,  -88,  -84,  -81,  -81,  -81,  -79,  -78,  -77,  -77,  -76,
        -76,  -74,  -73,  -73,  -71,  -71,  -70,  -69,  -68,  -66,  -65,  -65,
        -59,  -58,  -57,  -57,  -56,  -52,  -51,  -49,  -49,  -44,  -43,  -43,
        -40,  -38,  -38,  -37,  -36,  -35,  -33,  -32,  -32,  -31,  -31,  -28,
        -26,  -25,  -23,  -21,  -21,  -19,  -19,  -18,  -16,  -16,  -13,  -12,
        -11,  -10,  -9,   -8,   -8,   -6,   -5,   -5,   -4,   -2,   -2,   -1,
        -1,   -1,   0,    1,    5,    5,    6,    9,    9,    11,   12,   13,
        13,   15,   16,   17,   18,   18,   20,   20,   22,   23,   23,   23,
        24,   24,   24,   25,   27,   29,   32,   33,   33,   34,   34,   34,
        34,   35,   36,   37,   38,   39,   39,   41,   42,   45,   47,   48,
        48,   49,   49,   50,   51,   52,   52,   52,   52,   54,   54,   55,
        57,   59,   59,   60,   61,   62,   63,   64,   65,   66,   66,   67,
        67,   69,   72,   74,   75,   77,   77,   81,   82,   83,   86,   89,
        89,   90,   91,   96,   96,   98,   98,   99,   99,   99,   100,  103,
        103,  105,  107,  108,  109,  110,  112,  113,  115,  116,  116,  116,
        117,  120,  122,  122,  122,  123,  125,  125,  126,  127,  127,  129,
        129,  132,  132,  134,  135,  136,  137,  142,  142,  142,  142,  143,
        143,  144,  147,  147,  148,  148,  149,  149,  150,  154,  155,  156,
        158,  165,  167,  167,  170,  172,  179,  181,  182,  183,  185,  185,
        186,  186,  187,  188,  188,  189,  190,  191,  192,  192,  193,  197,
        198,  199,  199,  199,  200,  200,  201,  202,  203,  203,  205,  206,
        207,  211,  213,  215,  215,  216,  219,  222,  222,  223,  223,  224,
        224,  227,  228,  228,  230,  230,  232,  233,  235,  236,  236,  237,
        240,  240,  242,  243,  244,  245,  248,  248,  249,  250,  250,  250,
        252,  254,  255,  256,  258,  260,  262,  263,  264,  266,  268,  269,
        270,  272,  272,  274,  275,  277,  278,  278,  278,  279,  279,  280,
        281,  282,  285,  286,  286,  287,  291,  291,  293,  295,  296,  296,
        297,  297,  297,  298,  301,  302,  304,  304,  305,  305,  308,  308,
        308,  311,  311,  311,  312,  314,  314,  316,  317,  319,  319,  319,
        320,  321,  323,  323,  323,  325,  326,  326,  327,  328,  329,  329,
        331,  331,  332,  332,  332,  333,  333,  335,  335,  336,  337,  339,
        339,  340,  342,  342,  343,  343,  345,  346,  347,  347,  348,  348,
        349,  350,  350,  350,  352,  353,  353,  354,  355,  355,  355,  355,
        357,  357,  357,  357,  358,  358,  359,  360,  360,  361,  362,  363,
        364,  364,  364,  365,  365,  365,  367,  369,  370,  370,  371,  371,
        372,  373,  373,  373,  375,  376,  377,  379,  380,  382,  382,  383,
        384,  384,  385,  385,  386,  388,  391,  391,  393,  394,  394,  396,
        398,  398,  399,  401,  402,  402,  403,  403,  406,  407,  407,  408,
        408,  409,  412,  415,  415,  416,  417,  417,  417,  418,  420,  421,
        421,  422,  423,  424,  427,  427,  429,  429,  430,  433,  436,  436,
        439,  440,  445,  445,  447,  448,  451,  451,  452,  453,  456,  456,
        457,  458,  458,  459,  459,  459,  460,  460,  461,  462,  463,  463,
        463,  464,  468,  469,  470,  471,  472,  475,  476,  476,  477,  479,
        479,  480,  481,  482,  483,  484,  484,  485,  485,  487,  488,  488,
        489,  489,  489,  490,  492,  495,  495,  495,  498,  498,  498,  500};

    constexpr u64 k = 526603;
    constexpr i64 expected = 61578;

    // print_prods(nums1, nums2);
    ASSERT_EQ(Solution{}.kthSmallestProduct(nums1, nums2, k), expected);
}

TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_4)
{
    std::vector nums1{-2, -1, 0, 1, 2};
    std::vector nums2{-3, -1, 2, 4, 5};

    constexpr u64 k = 3;
    constexpr i64 expected = -6;

    print_prods(nums1, nums2);
    ASSERT_EQ(Solution{}.kthSmallestProduct(nums1, nums2, k), expected);
}

TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_5)
{
    std::vector nums1{-5};
    std::vector nums2{1};

    constexpr u64 k = 1;
    constexpr i64 expected = -5;

    print_prods(nums1, nums2);
    ASSERT_EQ(Solution{}.kthSmallestProduct(nums1, nums2, k), expected);
}

// TEST(t2240_kth_smallest_product_of_two_sorted_arrays, test_3)
// {
//     std::vector<int> nums1;
//     std::vector<int> nums2{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
//     std::vector<i64> prods;

//     auto check = [&](i64 x)
//     {
//         prods.clear();
//         for (int a : nums1)
//         {
//             for (int b : nums2)
//             {
//                 prods.push_back(i64{a} * i64{b});
//             }
//         }

//         std::ranges::sort(prods);
//         std::println("prods: {}", prods);
//         return static_cast<u64>(
//             std::distance(prods.begin(), std::ranges::lower_bound(prods,
//             x)));
//     };

//     auto count_products_less_than = [&](i64 x)
//     {
//         auto i = nums1.begin();

//         u64 total = 0;
//         while (i != nums1.end())
//         {
//             i64 v = *i;
//             auto next_i = std::ranges::upper_bound(nums1, v);

//             if (v == 0)
//             {
//                 total += x > 0 ? nums2.size() : 0;
//             }
//             else
//             {
//                 auto cnt1 = static_cast<u64>(std::distance(i, next_i));

//                 u64 cnt2 = 0;
//                 if (v < 0)
//                 {
//                     // if v < 0 then sequence of products is descending
//                     // [-5]
//                     // [-2, -1, 3]
//                     // [10, 5, -15]
//                     auto it = std::ranges::upper_bound(
//                         nums2,
//                         x,
//                         std::greater{},
//                         [&](int v2) { return i64{v2} * v; });

//                     cnt2 += static_cast<u64>(std::distance(it, nums2.end()));
//                 }
//                 else
//                 {
//                     // if v > 0 then sequence of products is ascending
//                     // [5]
//                     // [-2, -1, 3]
//                     // [-10, -5, 15]
//                     auto it = std::ranges::lower_bound(
//                         nums2,
//                         x,
//                         std::less{},
//                         [&](int v2) { return i64{v2} * v; });

//                     cnt2 += static_cast<u64>(std::distance(nums2.begin(),
//                     it));
//                 }

//                 total += cnt1 * cnt2;
//             }

//             i = next_i;
//         }

//         return total;
//     };

//     for (int a = -10; a != 11; ++a)
//     {
//         nums1 = {a};
//         for (int x = -5; x != 6; ++x)
//         {
//             ASSERT_EQ(check(x), count_products_less_than(x))
//                 << "x = " << x << "; a = " << a;
//         }
//     }
// }
