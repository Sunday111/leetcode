#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"

template <typename B>
class PbsInitializeTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsInitializeTest, PbsTypes);

TYPED_TEST(PbsInitializeTest, Operations)
{
    using B = TypeParam;
    pbs_initialize(this->bits, kFull);
    for (auto& bit : this->expected) bit = true;
    this->expect_valid();
    pbs_initialize<false>(this->bits);
    for (auto& bit : this->expected) bit = false;
    this->expect_valid();
    pbs_initialize<true>(this->bits);
    pbs_initialize(this->bits, kEmpty);
    this->expect_valid();
    const u32 end = B::kCapacity / 2;
    pbs_initialize(this->bits, kFull, end);
    for (u32 i = 0; i != end; ++i) this->expected[i] = true;
    this->expect_valid();
    pbs_initialize(this->bits, kEmpty, end);
    for (auto& bit : this->expected) bit = false;
    this->expect_valid();
    pbs_initialize(this->bits, kFull);
    pbs_initialize(this->bits, kEmpty, 0);
    EXPECT_TRUE(pbs_is_empty(this->bits));
    pbs_initialize(this->bits, kFull, 0);
    EXPECT_TRUE(pbs_is_empty(this->bits));
}
