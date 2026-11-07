#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_add_ex.hpp"

template <typename B>
class PbsAddExTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsAddExTest, PbsTypes);

TYPED_TEST(PbsAddExTest, Operations)
{
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        EXPECT_EQ(pbs_add_ex(this->bits, v), !this->expected[v]);
        this->expected[v] = true;
        EXPECT_FALSE(pbs_add_ex(this->bits, v));
    }
    this->expect_valid();
}
