#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_next.hpp"

template <typename B>
class PbsNextTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsNextTest, PbsTypes);

TYPED_TEST(PbsNextTest, Operations)
{
    const typename TypeParam::WordType* data = this->bits.words;
    const auto readonly = pbs_make<TypeParam::kCapacity>(data);
    EXPECT_EQ(pbs_next(readonly, 0), this->capacity);
    for (u32 step = 0; step != 128; ++step)
    {
        const auto v = this->sample(step);
        this->expected[v] = !this->expected[v];
        this->rebuild();
        for (const auto query : {v, this->sample(step + 2)})
        {
            u32 want = u32{query} + 1;
            while (want < this->capacity && !this->expected[want]) ++want;
            EXPECT_EQ(pbs_next(readonly, query), want);
        }
    }
    this->expect_valid();
}
