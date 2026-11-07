#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_add_if.hpp"

template <typename B>
class PbsAddIfTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsAddIfTest, PbsTypes);

TYPED_TEST(PbsAddIfTest, Operations)
{
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        const bool enabled = step % 3 != 0;
        pbs_add_if(this->bits, v, enabled);
        this->expected[v] |= enabled;
    }
    this->expect_valid();
}
