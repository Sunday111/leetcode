#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_set.hpp"

template <typename B>
class PbsSetTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsSetTest, PbsTypes);

TYPED_TEST(PbsSetTest, Operations)
{
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        pbs_set<true>(this->bits, v);
        EXPECT_TRUE(
            this->bits.words[v / TypeParam::kWordSize] &
            (typename TypeParam::WordType{1} << (v % TypeParam::kWordSize)));
        this->expected[v] = true;
        pbs_set<false>(this->bits, v);
        EXPECT_FALSE(
            this->bits.words[v / TypeParam::kWordSize] &
            (typename TypeParam::WordType{1} << (v % TypeParam::kWordSize)));
        this->expected[v] = false;
        const bool value = step % 3 != 0;
        pbs_set(this->bits, v, value);
        this->expected[v] = value;
    }
    this->expect_valid();
}
