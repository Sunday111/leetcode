#include <random>

#include "3721_longest_balanced_subarray_ii.hpp"
#include "gtest/gtest.h"

std::optional<u32>
ref_find_first(const std::vector<int>& ref, int value, Interval interval)
{
    for (u32 i = interval.begin; i < interval.end; ++i)
    {
        if (ref[i] == value) return i;
    }
    return std::nullopt;
}

TEST(SegmentTree, FuzzyRangeAddPointQueryAndFindFirst)
{
    constexpr u32 N = 1111;
    constexpr u32 OPS = 100'000;

    std::vector<SegmentTree::Node> nodes(num_required_nodes(N));

    for (int passsss = 0; passsss != 1; ++passsss)
    {
        SegmentTree st(nodes.data(), N);

        std::vector<int> ref(N, 0);

        std::mt19937 rng(123456);
        std::uniform_int_distribution<int> dist_val(-5, 5);
        std::uniform_int_distribution<u32> dist_idx(0, N - 1);
        std::uniform_int_distribution<int> dist_op(0, 2);

        for (u32 step = 0; step < OPS; ++step)
        {
            int op = dist_op(rng);

            if (op == 0)
            {
                // Range add
                u32 l = dist_idx(rng);
                u32 r = dist_idx(rng);
                if (l > r) std::swap(l, r);
                ++r;  // make [l, r)

                int delta = dist_val(rng);

                st.update({l, r}, delta);
                for (u32 i = l; i < r; ++i) ref[i] += delta;
            }
            else if (op == 1)
            {
                // Point query
                u32 idx = dist_idx(rng);
                int got = st.query(idx);
                ASSERT_EQ(got, ref[idx])
                    << "Mismatch at index " << idx << " on step " << step;
            }
            else
            {
                // find_first
                u32 l = dist_idx(rng);
                u32 r = dist_idx(rng);
                if (l > r) std::swap(l, r);
                ++r;

                int value = dist_val(rng);

                auto got = st.find_first(value, {l, r});
                auto exp = ref_find_first(ref, value, {l, r});

                ASSERT_EQ(got.has_value(), exp.has_value())
                    << "Presence mismatch for value " << value << " in [" << l
                    << ", " << r << ")";

                if (got && exp)
                {
                    ASSERT_EQ(*got, *exp) << "Wrong index for value " << value
                                          << " in [" << l << ", " << r << ")";
                }
            }
        }
    }
}

TEST(t3721_longest_balanced_subarray_ii, test_1)
{
    std::vector nums{2, 5, 4, 3};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 4);
}

TEST(t3721_longest_balanced_subarray_ii, test_2)
{
    std::vector nums{3, 2, 2, 5, 4};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 5);
}

TEST(t3721_longest_balanced_subarray_ii, test_3)
{
    std::vector nums{1, 2, 3, 2};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 3);
}
TEST(t3721_longest_balanced_subarray_ii, test_4)
{
    std::vector nums{19, 5, 41, 39, 39, 23, 20};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 2);
}

/*
[3,2,2,5,4]
[1,2,3,2]
[1,3,2,1,1]
[3,2,2,5,4]
[1,2,3,2]
[8,2,8,8,1,1,2,3]
[4,4,4,1,3,5,7,9,11,13,2,4,6,6,6]
[19,5,41,39,39,23 ,20]
*/
