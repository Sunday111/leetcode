#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <typename B>
class PbsLayersTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsLayersTest, PbsTypes);

TYPED_TEST(PbsLayersTest, Operations)
{
    using B = TypeParam;
    u32 index = 0;
    u32 count = B::kCapacity;
    u32 offset = 0;
    pbs_for_each_layer<B>(
        [&](auto layer)
        {
            EXPECT_EQ(layer, index++);
            count = (count + B::kWordSize - 1) / B::kWordSize;
            EXPECT_EQ(B::kLayersSizes[layer], count);
            EXPECT_EQ(B::offsets[layer], offset);
            offset += count;
        });
    EXPECT_EQ(count, 1);
    EXPECT_EQ(offset, B::kTotalWords);
    pbs_for_each_layer_reversed<B>([&](auto layer)
                                   { EXPECT_EQ(layer, --index); });
    EXPECT_EQ(index, 0);
    if constexpr (B::kNumLayers > 1)
        EXPECT_GT(B::kLayersSizes[B::kNumLayers - 2], 1);
}
static_assert(PyramidBitset<64>::kNumLayers == 1);
static_assert(PyramidBitset<4096>::kNumLayers == 2);
static_assert(PyramidBitset<4097>::kNumLayers == 3);
