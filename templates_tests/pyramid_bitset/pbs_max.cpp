#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_max.hpp"

template <typename B>
class PbsMaxTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsMaxTest, PbsTypes);

TYPED_TEST(PbsMaxTest, Operations)
{
    for (u32 step = 0; step != 128; ++step)
        this->expected[this->sample(step)] = true;
    this->rebuild();
    u32 remaining = 0;
    for (bool bit : this->expected) remaining += bit;
    while (remaining-- != 0)
    {
        u32 expected = this->capacity - 1;
        while (!this->expected[expected]) --expected;
        EXPECT_EQ(pbs_max(this->bits), expected);
        this->expected[expected] = false;
        this->rebuild();
    }
    this->expect_valid();
}
