#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "pyramid_bitset/pbs_remove_ex.hpp"
template <typename B>
class PbsRemoveExTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsRemoveExTest, PbsTypes);

TYPED_TEST(PbsRemoveExTest, Operations)
{
    for (auto& bit : this->expected) bit = true;
    this->rebuild();
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        EXPECT_EQ(pbs_remove_ex(this->bits, v), this->expected[v]);
        this->expected[v] = false;
        EXPECT_FALSE(pbs_remove_ex(this->bits, v));
    }
    this->expect_valid();
    for (u32 i = 0; i != this->capacity; ++i)
    {
        pbs_remove(this->bits, i & this->index_mask);
        this->expected[i] = false;
    }
    this->expect_valid();
}
