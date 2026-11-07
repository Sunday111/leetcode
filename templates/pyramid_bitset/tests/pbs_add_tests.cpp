#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_add.hpp"

template <typename B>
class PbsAddTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsAddTest, PbsTypes);

TYPED_TEST(PbsAddTest, Operations)
{
    for (u32 step = 0; step != 256; ++step)
    {
        const auto v = this->sample(step);
        pbs_add(this->bits, v);
        this->expected[v] = true;
    }
    this->expect_valid();
}
