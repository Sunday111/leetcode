#include "0215_kth_largest_element_in_an_array.hpp"
#include "gtest/gtest.h"

TEST(t0215_kth_largest_element_in_an_array, test_1)
{
    PyramidBitset<20'000> lbs;
    lbs.add(1234);
    lbs.add(5932);
    ASSERT_EQ(lbs.lowest(), 1234);
    lbs.remove(1234);
    ASSERT_EQ(lbs.lowest(), 5932);

    std::vector<int> nums{0, 1, 2, 3, 4, 5, 9999};
    ASSERT_EQ(Solution{}.findKthLargest(nums, 1), 9999);
}

TEST(LayeredBitsetTest, RemoveOneBitFromNonEmptyWord)
{
    PyramidBitset<130> bs;  // 130 requires multiple layers

    // Add two bits in the same lower-layer word
    bs.add(0);  // bit 0
    bs.add(1);  // bit 1

    // Verify both bits are set
    EXPECT_TRUE(bs.get(0));
    EXPECT_TRUE(bs.get(1));

    // Remove the first bit
    bs.remove(0);

    // The second bit should still be set
    EXPECT_TRUE(bs.get(1));

    // Lowest should now return 1
    EXPECT_EQ(bs.lowest(), 1u);

    // Remove the remaining bit
    bs.remove(1);

    // Now the bitset is empty; get should be false
    EXPECT_FALSE(bs.get(0));
    EXPECT_FALSE(bs.get(1));
}

// Optional: test larger numbers and multiple layers
TEST(LayeredBitsetTest, MultipleLayers)
{
    PyramidBitset<5000> bs;

    bs.add(1234);
    bs.add(4321);
    bs.add(4999);

    EXPECT_EQ(bs.lowest(), 1234);

    bs.remove(1234);
    EXPECT_EQ(bs.lowest(), 4321);

    bs.remove(4321);
    EXPECT_EQ(bs.lowest(), 4999);
}
