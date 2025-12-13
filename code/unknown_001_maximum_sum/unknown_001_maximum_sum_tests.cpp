#include <random>

#include "gtest/gtest.h"
#include "unknown_001_maximum_sum.hpp"

// TEST(tunknown_001_maximum_sum, test_brute)
// {
//     std::vector<std::vector<u32>> m{{
//         {3, 7, 2},
//         {4, 1, 5},
//     }};
//     ASSERT_EQ(Solution{}.maximumSumBrute(m, 3), 15);
// }

// TEST(tunknown_001_maximum_sum, test_1)
// {
//     const u32 k = 3;
//     std::vector<std::vector<u32>> m{{
//         {3, 7, 2},
//         {4, 1, 5},
//     }};
//     ASSERT_EQ(Solution{}.maximumSumBrute(m, k), Solution{}.maximumSum(m, k));
// }

TEST(tunknown_001_maximum_sum, test_2)
{
    const u32 k = 5;
    constexpr std::array<u32, 6> m{
        33,
        99,
        33,
        99,
        33,
        99,
    };
    MatrixView<const u32> view{m.data(), 3, 2};
    ASSERT_EQ(
        Solution{}.maximumSumBrute(view, k),
        Solution{}.maximumSum(view, k));
}

template <typename T>
void print_matrix(std::string_view prefix, MatrixView<T> m)
{
    for (u32 y = 0; y != m.extent(0); ++y)
    {
        std::print("{}", prefix);
        for (u32 x = 0; x != m.extent(1); ++x)
        {
            std::print("{:<4}", m[y, x]);
        }
        std::println("");
    }
}

TEST(tunknown_001_maximum_sum, test_fuzz_memo)
{
    static constexpr u32 kSeed = 1234;
    std::mt19937_64 rnd(kSeed);

    std::uniform_int_distribution<u32> val_distr(1, 100);
    u32 dim_lim = 6;
    u32 num_passes = 20;

    std::vector<u32> data(dim_lim * dim_lim + num_passes);
    std::generate_n(data.begin(), data.size(), std::bind_front(val_distr, rnd));

    for (u32 n = 1; n != dim_lim; ++n)
    {
        for (u32 m = 1; m != dim_lim; ++m)
        {
            for (u32 lim_k = m * n, k = 1; k != lim_k; ++k)
            {
                for (u32 pass = 0; pass != num_passes; ++pass)
                {
                    MatrixView<const u32> matrix{data.data() + pass, m, n};

                    const u32 expected = Solution{}.maximumSumBrute(matrix, k);
                    const u32 actual = Solution{}.maximumSumMemo(matrix, k);

                    if (expected != actual)
                    {
                        std::println("k = {}, n = {}, m = {}", k, n, m);
                        std::println("matrix: ");
                        print_matrix("    ", matrix);
                    }

                    ASSERT_EQ(expected, actual);
                }
            }
        }
    }
}

TEST(tunknown_001_maximum_sum, test_fuzz_dp)
{
    static constexpr u32 kSeed = 1234;
    std::mt19937_64 rnd(kSeed);

    std::uniform_int_distribution<u32> val_distr(1, 100);
    u32 dim_lim = 20;
    u32 num_passes = 40;
    std::vector<u32> data(dim_lim * dim_lim + num_passes);
    std::generate_n(data.begin(), data.size(), std::bind_front(val_distr, rnd));

    for (u32 n = 1; n != dim_lim; ++n)
    {
        for (u32 m = 1; m != dim_lim; ++m)
        {
            for (u32 lim_k = m * n, k = 1; k != lim_k; ++k)
            {
                for (u32 pass = 0; pass != num_passes; ++pass)
                {
                    MatrixView<const u32> matrix{data.data() + pass, m, n};

                    const u32 expected = Solution{}.maximumSumMemo(matrix, k);
                    const u32 actual = Solution{}.maximumSum(matrix, k);

                    if (expected != actual)
                    {
                        std::println("k = {}, n = {}, m = {}", k, n, m);
                        std::println("matrix: ");
                        print_matrix("    ", matrix);
                    }

                    ASSERT_EQ(expected, actual);
                }
            }
        }
    }
}
