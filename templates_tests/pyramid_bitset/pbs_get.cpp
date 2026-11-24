#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_get.hpp"

template <typename B>
class PbsGetTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsGetTest, PbsTypes);

TYPED_TEST(PbsGetTest, Operations)
{
    for (u32 step = 0; step != 256; ++step)
        this->expected[this->sample(step)] = true;
    this->rebuild();
    const typename TypeParam::WordType* words = this->bits.words;
    const auto readonly = pbs_make<TypeParam::kCapacity>(words);
    for (u32 i = 0; i != this->capacity; ++i)
    {
        EXPECT_EQ(pbs_get(readonly, i & this->index_mask), this->expected[i]);
    }
    this->expect_valid();
}
