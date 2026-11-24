#include "pyramid_bitset/pbs_required_buffer_words.hpp"

static_assert(std::is_same_v<PyramidBitset<128>::WordType, u64>);
static_assert(pbs_required_buffer_words<1>() == 1);
static_assert(pbs_required_buffer_words<64>() == 1);
static_assert(pbs_required_buffer_words<65>() == 3);
static_assert(pbs_required_buffer_words<128>() == 3);
static_assert(pbs_required_buffer_words<128, u128>() == 1);
static_assert(pbs_required_buffer_words<129, u128>() == 3);
static_assert(pbs_required_buffer_words<4097>() == 65 + 2 + 1);
