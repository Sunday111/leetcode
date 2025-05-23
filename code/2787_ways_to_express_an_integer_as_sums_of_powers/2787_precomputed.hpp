#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>

template <typename T, size_t... sizes>
static inline constexpr auto joinArrays(const std::array<T, sizes>&... arrays)
{
    constexpr size_t total_size = (0 + ... + sizes);
    std::array<T, total_size> r;  // NOLINT
    uint32_t num_added = 0;

    (
        [&](const auto& arr)
        {
            std::ranges::copy(arr, std::next(r.begin(), num_added));
            num_added += arr.size();
        }(arrays),
        ...);
    return r;
}

class Solution
{
public:
    static inline constexpr std::array kPrecomputedAnswers = joinArrays(
        std::array{
            1,         1,         2,         2,         3,         4,
            5,         6,         8,         10,        12,        15,
            18,        22,        27,        32,        38,        46,
            54,        64,        76,        89,        104,       122,
            142,       165,       192,       222,       256,       296,
            340,       390,       448,       512,       585,       668,
            760,       864,       982,       1113,      1260,      1426,
            1610,      1816,      2048,      2304,      2590,      2910,
            3264,      3658,      4097,      4582,      5120,      5718,
            6378,      7108,      7917,      8808,      9792,      10880,
            12076,     13394,     14848,     16444,     18200,     20132,
            22250,     24576,     27130,     29927,     32992,     36352,
            40026,     44046,     48446,     53250,     58499,     64234,
            70488,     77312,     84756,     92864,     101698,    111322,
            121792,    133184,    145578,    159046,    173682,    189586,
            206848,    225585,    245920,    267968,    291874,    317788,
            345856,    376256,    409174,    444793,    483330,    525016,
            570078,    618784,    671418,    728260,    789640,    855906,
            927406,    1004544,   1087744,   1177438,   1274118,   1378304,
            1490528,   1611388,   1741521,   1881578,   2032290,   2194432,
            2368800,   2556284,   2757826,   2974400,   3207086,   3457027,
            3725410,   4013544,   4322816,   4654670,   5010688,   5392550,
            5802008,   6240974,   6711480,   7215644,   7755776,   8334326,
            8953856,   9617150,   10327156,  11086968,  11899934,  12769602,
            13699699,  14694244,  15757502,  16893952,  18108418,  19406016,
            20792120,  22272512,  23853318,  25540982,  27342421,  29264960,
            31316314,  33504746,  35839008,  38328320,  40982540,  43812110,
            46828032,  50042056,  53466624,  57114844,  61000704,  65139008,
            69545358,  74236384,  79229676,  84543782,  90198446,  96214550,
            102614114, 109420549, 116658616, 124354422, 132535702, 141231780,
            150473568, 160293888, 170727424, 181810744, 193582642, 206084096,
            219358315, 233451098, 248410816, 264288462, 281138048, 299016608,
            317984256, 338104630, 359444904, 382075868, 406072422, 431513602,
            458482688, 487067746, 517361670, 549462336, 583473184, 619503296,
            657667584, 698087424, 740890786, 786212446, 834194700, 884987529,
            938748852, 995645336, 55852583,  119555481, 186949049, 258238713,
            333640703, 413383019, 497705761, 586861599, 681116845, 780751876,
            886061677, 997357049, 114965106, 239229946, 370513972, 509198514,
            655684594, 810394440, 973772198, 146284849, 328423915, 520706283,
            723675305, 937902667, 163989430, 402567296, 654300678, 919887964,
            200062941, 495597213, 807301597, 136027832, 482671280, 848172562,
            233519570, 639750473, 67955656,  519280072, 994926546, 496158145,

            24300820,  580747194, 166959261, 784471471,
        },
        std::array{
            434894980, 119920837, 841323491, 600965607, 400801751, 242882448,
            129359625, 62490848,  44644013,  78303480,  166074989, 310691038,
            515017823, 782060902, 114971358, 517053693, 991772290, 542758528,
            173819680, 888946369, 692320715, 588326383, 581557167, 676826337,
            879177939, 193896710, 626518758, 182844315, 868949151, 691196692,
            656252574, 771097590, 43041626,  479740071, 89208609,  879839212,
            860418576, 40145155,  428647317, 36004210,  872765252, 949970735,
            279175535, 872471266, 1,         0,         0,         1,
            1,         0,         0,         0,         1,         1,
            0,         0,         1,         1,         0,         1,
            1,         0,         0,         1,         1,         0,
            0,         0,         2,         2,         0,         0,
            2,         2,         0,         0,         0,         1,
            1,         1,         1,         1,         1,         1,
            2,         1,         0,         0,         2,         2,
            0,         0,         2,         3,         1,         1,
            2,         2,         1,         1,         1,         1,
            1,         0,         2,         3,         1,         1,
            4,         3,         0,         1,         2,         2,
            1,         0,         1,         4,         3,         0,
            2,         4,         2,         1,         3,         2,
            1,         2,         3,         3,         2,         1,
            3,         6,         3,         0,         2,         5,
            3,         0,         1,         3,         3,         3,
            4,         3,         2,         3,         4,         4,
            2,         0,         3,         7,         4,         0,
            3,         6,         4,         3,         4,         3,
            3,         4,         4,         4,         3,         1,
            5,         9,         4,         0,         5,         9,
            5,         1,         2,         6,         6,         3,
            3,         6,         6,         3,         4,         7,
            5,         2,         5,         9,         6,         2,
            5,         9,         7,         3,         4,         7,
            8,         5,         3,         7,         8,         4,
            5,         8,         5,         4,         8,         8,
            5,         4,         7,         11,        9,         3,
            5,         13,        11,        3,         3,         9,
            9,         6,         6,         8,         9,         7,
            9,         12,        8,         2,         7,         14,
            10,        3,         4,         14,        16,        8,
            5,         11,        13,        9,         8,         8,
            8,         7,         10,        14,        11,        6,
            9,         18,        15,        6,
        },
        std::array{
            5,  12, 14, 8,  6,  10, 15, 11, 11, 16, 13, 7,  12, 17, 11, 6,
            8,  17, 19, 10, 8,  20, 21, 9,  9,  17, 16, 8,  9,  15, 16, 12,
            11, 19, 20, 12, 10, 21, 20, 8,  8,  19, 23, 13, 10, 18, 25, 19,
            14, 15, 18, 17, 13, 17, 18, 12, 14, 28, 25, 11, 14, 26, 27, 16,
            11, 16, 25, 21, 14, 20, 24, 17, 18, 31, 23, 9,  16, 31, 28, 13,
            11, 25, 36, 24, 12, 21, 33, 25, 1,  0,  0,  0,  0,  0,  0,  1,
            1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,
            1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
            1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,
        },
        std::array{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
            0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        std::array{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        std::array{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int32_t numberOfWays(int32_t n, int32_t x)
    {
        return kPrecomputedAnswers[std::bit_cast<uint32_t>(
            (x - 1) * 300 + n - 1)];
    }
};
