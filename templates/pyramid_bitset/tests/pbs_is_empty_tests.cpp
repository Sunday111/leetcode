#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"

template <typename B>
class PbsIsEmptyTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsIsEmptyTest, PbsTypes);

TYPED_TEST(PbsIsEmptyTest, Operations)
{
    EXPECT_TRUE(pbs_is_empty(this->bits));
    for (u32 step = 0; step != 64; ++step)
    {
        const auto v = this->sample(step);
        this->expected[v] = true;
        this->rebuild();
        EXPECT_FALSE(pbs_is_empty(this->bits));
        this->expected[v] = false;
        this->rebuild();
        EXPECT_TRUE(pbs_is_empty(this->bits));
    }
    this->expect_valid();
}
