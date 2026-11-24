#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_min.hpp"

template <typename B>
class PbsMinTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsMinTest, PbsTypes);

TYPED_TEST(PbsMinTest, Operations)
{
    for (u32 step = 0; step != 128; ++step)
        this->expected[this->sample(step)] = true;
    this->rebuild();
    u32 remaining = 0;
    for (bool bit : this->expected) remaining += bit;
    while (remaining-- != 0)
    {
        u32 expected = 0;
        while (!this->expected[expected]) ++expected;
        EXPECT_EQ(pbs_min(this->bits), expected);
        this->expected[expected] = false;
        this->rebuild();
    }
    this->expect_valid();
}
