#include "2916_segment_tree.hpp"
#include "2916_test_cases.hpp"
#include "gtest/gtest.h"

TEST(BIT2916, DistinctCountUpdatesAndStorageReset)
{
    BIT<5> bit(5);
    bit.update(0, 0);
    EXPECT_EQ(bit.query(0, 4), 1u);
    bit.update(0, 1);
    EXPECT_EQ(bit.query(0, 4), 3u);
    bit.update(1, 2);
    EXPECT_EQ(bit.query(0, 4), 5u);
    EXPECT_EQ(bit.query(1, 2), 3u);
    EXPECT_EQ(bit.suffix_sum(1), 3u);
    bit.update(0, 3);
    bit.update(4, 4);
    EXPECT_EQ(bit.query(0, 4), 10u);
    EXPECT_EQ(bit.query(4, 4), 1u);
    EXPECT_EQ(bit.suffix_sum(0), 10u);
    EXPECT_EQ(bit.suffix_sum(5), 0u);

    BIT<5> reset_bit(5);
    EXPECT_EQ(reset_bit.query(0, 4), 0u);
    EXPECT_EQ(reset_bit.suffix_sum(0), 0u);
}

TEST(BIT2916, LargeRangeSums)
{
    constexpr u32 n = 100'000;
    BIT<n> bit(n);
    for (u32 r = 0; r < n; ++r) bit.update(0, r);
    EXPECT_EQ(bit.query(0, n - 1), u64{n} * (n + 1) / 2);
    EXPECT_EQ(bit.query(n - 1, n - 1), 1u);

    // The Fenwick bucket ending at 98304 exceeds signed 32-bit capacity.
    constexpr u32 l = 65'536, r = 98'303;
    EXPECT_EQ(bit.query(l, r), u64{r - l + 1} * (2 * n - l - r) / 2);
}

TEST(SegmentTree2916, InitializesStorage)
{
    SegmentTree<SumSquaresNode, 4> tree(4);

    tree.update(0, 3, 1);
    EXPECT_EQ(tree.root().sum, 4u);
    EXPECT_EQ(tree.root().sq, 4u);

    tree.update(1, 2, 1);
    EXPECT_EQ(tree.root().sum, 6u);
    EXPECT_EQ(tree.root().sq, 10u);

    SegmentTree<SumSquaresNode, 4> reset_tree(4);
    EXPECT_EQ(reset_tree.root().sum, 0u);
    EXPECT_EQ(reset_tree.root().sq, 0u);
}

TEST(Solution2916, DistinctValuesModulo)
{
    std::vector<int> nums(1000);
    for (u32 i = 0; i < nums.size(); ++i)
    {
        nums[i] = static_cast<int>(i + 1);
    }

    Solution solution;
    EXPECT_EQ(solution.sumCounts(nums), 667082919u);
}

TEST(Solution2916, MaximumDistinctValues)
{
    constexpr u32 n = 100'000;
    std::vector<int> nums(n);
    u64 expected = 0;
    for (u32 i = 0; i < n; ++i)
    {
        nums[i] = static_cast<int>(i + 1);
        u64 len = i + 1;
        expected += (n - len + 1) * len * len;
    }

    Solution solution;
    EXPECT_EQ(solution.sumCounts(nums), expected % 1'000'000'007);
}

TEST(SegmentTree2916, PowerOfTwoBoundaries)
{
    for (u32 n : {1u, 65'535u, 65'536u, 65'537u, 100'000u})
    {
        SegmentTree<SumSquaresNode, 100'000> tree(n);
        tree.update(0, n - 1, 1);
        EXPECT_EQ(tree.root().sum, n);
        EXPECT_EQ(tree.root().sq, n);

        tree.update(n - 1, n - 1, 1);
        EXPECT_EQ(tree.root().sum, n + 1);
        EXPECT_EQ(tree.root().sq, n + 3);
    }
}

TEST(SegmentTree2916, RangeAssignment)
{
    struct AssignSumNode
    {
        using Update = u32;

        u64 sum = 0;
        u32 pending_value = 0;
        bool has_pending = false;

        void apply(Update value, u32 len)
        {
            sum = u64{value} * len;
            pending_value = value;
            has_pending = true;
        }

        void push(
            AssignSumNode& left,
            AssignSumNode& right,
            u32 left_len,
            u32 right_len)
        {
            if (!has_pending) return;
            left.apply(pending_value, left_len);
            right.apply(pending_value, right_len);
            has_pending = false;
        }

        void pull(const AssignSumNode& left, const AssignSumNode& right)
        {
            sum = left.sum + right.sum;
        }
    };

    SegmentTree<AssignSumNode, 5> tree(5);

    tree.update(0, 4, 7);
    EXPECT_EQ(tree.root().sum, 35u);
    tree.update(1, 3, 2);
    EXPECT_EQ(tree.root().sum, 20u);
    tree.update(0, 4, 0);
    EXPECT_EQ(tree.root().sum, 0u);
    tree.update(2, 2, 9);
    EXPECT_EQ(tree.root().sum, 9u);
}

class t2916 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2916, Test)
{
    auto [inputs, expected] = k_cases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(k_method_to_test, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);

    SegmentTreeSolution reference;
    auto reference_f =
        std::bind_front(&SegmentTreeSolution::sumCounts, &reference);
    EXPECT_EQ(expected, std::apply(reference_f, inputs));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2916,
    ::testing::Range(size_t{0}, k_cases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
