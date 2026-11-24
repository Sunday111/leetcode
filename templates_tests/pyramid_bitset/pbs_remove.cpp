#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

template <typename B>
class PbsRemoveTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsRemoveTest, PbsTypes);

TYPED_TEST(PbsRemoveTest, Operations)
{
    for (auto& bit : this->expected) bit = true;
    this->rebuild();
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        pbs_remove(this->bits, v);
        this->expected[v] = false;
        pbs_remove(this->bits, v);
    }
    this->expect_valid();
    for (u32 i = 0; i != this->capacity; ++i)
    {
        pbs_remove(this->bits, i & this->index_mask);
        this->expected[i] = false;
    }
    this->expect_valid();
}
