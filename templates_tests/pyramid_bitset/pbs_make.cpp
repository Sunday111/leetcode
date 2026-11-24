#include "pbs_test_support.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_required_buffer_words.hpp"

template <typename B>
class PbsMakeTest : public PbsTest<B>
{
};
TYPED_TEST_SUITE(PbsMakeTest, PbsTypes);

TYPED_TEST(PbsMakeTest, Operations)
{
    using B = TypeParam;
    static_assert(std::is_same_v<decltype(B::kCapacity), const u32>);
    static_assert(sizeof(B) == sizeof(typename B::WordType*));
    static_assert(std::is_trivially_copyable_v<B>);
    EXPECT_EQ(this->bits.words, this->storage + 1);
    this->expected[B::kCapacity - 1] = true;
    this->rebuild();
    const auto alias = pbs_make<B::kCapacity>(this->bits.words);
    EXPECT_EQ(alias.words, this->bits.words);
    alias.words[0] = 0;
    EXPECT_EQ(this->bits.words[0], 0);
    this->rebuild();
    const typename B::WordType* data = this->bits.words;
    const auto readonly = pbs_make<B::kCapacity>(data);
    static_assert(
        std::is_const_v<std::remove_pointer_t<decltype(readonly.words)>>);
    EXPECT_EQ(readonly.words, data);
    this->expect_valid();
}
static_assert(
    []
    {
        u128 words[pbs_required_buffer_words<129, u128>()]{17, 0, 1};
        const auto bits = pbs_make<129>(words);
        const auto alias = bits;
        alias.words[0] = 23;
        return bits.words == words && words[0] == 23 && words[2] == 1;
    }());

using LargestPbs = PyramidBitset<std::numeric_limits<u32>::max(), u128>;
static_assert(std::is_same_v<LargestPbs::WordType, u128>);
static_assert(LargestPbs::kCapacity == 0xFFFF'FFFFu);
static_assert(LargestPbs::kLayersSizes[0] == (u32{1} << 25));
static_assert(LargestPbs::kNumLayers == 5);
static_assert(LargestPbs::kTotalWords == 33'818'641);
