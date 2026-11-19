#include <algorithm>
#include <array>

#include "1569.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numOfWays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1] 0
[1,2] 0
[2,1] 0
[1,2,3,4,5] 0
[5,4,3,2,1] 0
[2,1,3] 1
[3,1,2,4] 2
[3,4,1,2] 2
[3,4,5,1,2] 5
[4,2,1,3,6,5,7] 79
[8,4,2,1,3,6,5,7,12,10,9,11,14,13,15] 21964799
[16,8,4,2,1,3,6,5,7,12,10,9,11,14,13,15,24,20,18,17,19,22,21,23,28,26,25,27,30,29,31] 203434153
)");

using t1569 = SolutionTests<Solution>;

TEST_P(t1569, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numOfWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1569,
    t1569::parameters(kCases.size()),
    t1569::name);

TEST(t1569Boundary, MaximumSkewedTrees)
{
    Solution instance{};
    std::vector<int> nums(1000);
    int value = 1;
    for (auto& num : nums) num = value++;
    EXPECT_EQ(instance.numOfWays(nums), 0u);
    value = 1000;
    for (auto& num : nums) num = value--;
    EXPECT_EQ(instance.numOfWays(nums), 0u);
}

TEST(t1569Boundary, MaximumBalancedTreeThenSingleton)
{
    std::vector<int> nums;
    auto append = [&](this auto&& self, int first, int last) -> void
    {
        if (first > last) return;
        int mid = (first + last) / 2;
        nums.push_back(mid);
        self(first, mid - 1);
        self(mid + 1, last);
    };
    append(1, 1000);
    Solution instance{};
    EXPECT_EQ(instance.numOfWays(nums), 718156653u);
    nums = {1};
    EXPECT_EQ(instance.numOfWays(nums), 0u);
}

TEST(t1569Construction, MatchesInsertionForEverySevenNodePermutation)
{
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7};
    do
    {
        std::array<Node, 7> expected{};
        for (size_t i = 0; i != nums.size(); ++i)
        {
            expected[i].v = nums[i] & 1023;
            if (i == 0) continue;
            u32 parent_id = 0;
            while (true)
            {
                auto& parent = expected[parent_id];
                bool left = nums[i] < parent.v;
                u32 child = left ? parent.l : parent.r;
                if (child != kNullNode)
                {
                    parent_id = child;
                    continue;
                }
                if (left)
                {
                    parent.l = i & 1023;
                }
                else
                {
                    parent.r = i & 1023;
                }
                break;
            }
        }
        Solution::construct_tree(nums);
        for (size_t i = 0; i != nums.size(); ++i)
        {
            ASSERT_EQ(u32{Solution::nodes[i].v}, u32{expected[i].v});
            ASSERT_EQ(u32{Solution::nodes[i].l}, u32{expected[i].l});
            ASSERT_EQ(u32{Solution::nodes[i].r}, u32{expected[i].r});
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
}
