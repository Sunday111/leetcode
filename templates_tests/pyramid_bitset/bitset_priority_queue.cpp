#include <set>
#include <utility>

#include "gtest/gtest.h"
#include "pyramid_bitset/bitset_priority_queue.hpp"

template <typename Q>
class BitsetPriorityQueueTest : public ::testing::Test
{
};
using QueueTypes = ::testing::Types<
    BitsetPriorityQueue<7, 512>,
    BitsetPriorityQueue<63, 512>,
    BitsetPriorityQueue<64, 512>,
    BitsetPriorityQueue<65, 512>,
    BitsetPriorityQueue<4096, 512>>;
TYPED_TEST_SUITE(BitsetPriorityQueueTest, QueueTypes);

TYPED_TEST(BitsetPriorityQueueTest, DuplicatesMinMaxAndClear)
{
    TypeParam queue;
    using V = typename TypeParam::ValueType;
    constexpr V last = TypeParam::B::kCapacity - 1;
    EXPECT_TRUE(queue.is_empty());
    for (u32 i = 0; i != 300; ++i) queue.add(last);
    queue.add(0);
    EXPECT_EQ(queue.min(), 0);
    EXPECT_EQ(queue.max(), last);
    EXPECT_EQ(queue.pop_min(), 0);
    for (u32 i = 0; i != 300; ++i) EXPECT_EQ(queue.pop_max(), last);
    EXPECT_TRUE(queue.is_empty());
    queue.add(last);
    queue.clear();
    EXPECT_TRUE(queue.is_empty());
    for (auto count : queue.freq) EXPECT_EQ(count, 0);
    queue.add(0);
    EXPECT_EQ(queue.pop_min(), 0);
    EXPECT_TRUE(queue.is_empty());
}

TYPED_TEST(BitsetPriorityQueueTest, CopiesOwnTheirStorage)
{
    TypeParam original;
    original.add(0);
    original.add(1);
    auto copy = original;
    copy.remove(0);
    EXPECT_EQ(original.min(), 0);
    EXPECT_EQ(copy.min(), 1);
    TypeParam assigned;
    assigned = original;
    original.clear();
    EXPECT_EQ(assigned.min(), 0);
    auto moved = std::move(assigned);
    moved.remove(0);
    EXPECT_EQ(moved.min(), 1);
    EXPECT_EQ(copy.min(), 1);
}

static_assert(
    []
    {
        BitsetPriorityQueue<64, 512> queue;
        queue.add(64);
        auto copy = queue;
        queue.clear();
        return queue.is_empty() && copy.pop_min() == 64 && copy.is_empty();
    }());
