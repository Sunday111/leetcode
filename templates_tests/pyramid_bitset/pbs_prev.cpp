#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_prev.hpp"

template <typename B>
class PbsPrevTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsPrevTest, PbsTypes);

TYPED_TEST(PbsPrevTest, Operations)
{
    const typename TypeParam::WordType* data = this->bits.words;
    const auto readonly = pbs_make<TypeParam::kCapacity>(data);
    EXPECT_EQ(pbs_prev(readonly, 0), this->capacity);
    for (u32 step = 0; step != 128; ++step)
    {
        const auto v = this->sample(step);
        this->expected[v] = !this->expected[v];
        this->rebuild();
        for (const auto query : {v, this->sample(step + 2)})
        {
            u32 want = query;
            while (want != 0 && !this->expected[want - 1]) --want;
            if (want == 0)
                want = this->capacity;
            else
                --want;
            EXPECT_EQ(pbs_prev(readonly, query), want);
        }
    }
    this->expect_valid();
}
