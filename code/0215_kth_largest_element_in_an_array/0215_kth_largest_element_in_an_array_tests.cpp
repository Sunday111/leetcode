#include "0215_kth_largest_element_in_an_array.hpp"
#include "gtest/gtest.h"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

TEST(t0215_kth_largest_element_in_an_array, test_1)
{
    PyramidBitset<20'000> lbs{};
    pbs_add(lbs, 1234);
    pbs_add(lbs, 5932);
    ASSERT_EQ(pbs_min(lbs), 1234);
    pbs_remove(lbs, 1234);
    ASSERT_EQ(pbs_min(lbs), 5932);

    std::vector<int> nums{0, 1, 2, 3, 4, 5, 9999};
    ASSERT_EQ(Solution{}.findKthLargest(nums, 1), 9999);
}

TEST(LayeredBitsetTest, RemoveOneBitFromNonEmptyWord)
{
    PyramidBitset<130> bs{};  // 130 requires multiple layers

    // Add two bits in the same lower-layer word
    pbs_add(bs, 0);  // bit 0
    pbs_add(bs, 1);  // bit 1

    // Verify both bits are set
    EXPECT_TRUE(pbs_get(bs, 0));
    EXPECT_TRUE(pbs_get(bs, 1));

    // Remove the first bit
    pbs_remove(bs, 0);

    // The second bit should still be set
    EXPECT_TRUE(pbs_get(bs, 1));

    // Lowest should now return 1
    EXPECT_EQ(pbs_min(bs), 1u);

    // Remove the remaining bit
    pbs_remove(bs, 1);

    // Now the bitset is empty; get should be false
    EXPECT_FALSE(pbs_get(bs, 0));
    EXPECT_FALSE(pbs_get(bs, 1));
}

// Optional: test larger numbers and multiple layers
TEST(LayeredBitsetTest, MultipleLayers)
{
    PyramidBitset<5000> bs{};

    pbs_add(bs, 1234);
    pbs_add(bs, 4321);
    pbs_add(bs, 4999);

    EXPECT_EQ(pbs_min(bs), 1234);

    pbs_remove(bs, 1234);
    EXPECT_EQ(pbs_min(bs), 4321);

    pbs_remove(bs, 4321);
    EXPECT_EQ(pbs_min(bs), 4999);
}
