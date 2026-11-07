#pragma once

#include <limits>
#include <random>
#include <type_traits>

#include "gtest/gtest.h"
#include "pyramid_bitset/pbs_make.hpp"

template <typename B>
class PbsTest : public ::testing::Test
{
public:
    using Word = typename B::WordType;
    using Index = typename B::ValueType;
    static constexpr u32 capacity = B::kCapacity;
    static constexpr Index index_mask = std::numeric_limits<Index>::max();
    Word storage[B::kTotalWords + 2]{};
    bool expected[capacity]{};
    const B bits = pbs_make<B::kCapacity>(storage + 1);
    std::mt19937 random{1606};

    PbsTest()
    {
        storage[0] = 73;
        storage[B::kTotalWords + 1] = 91;
    }

    Index sample(u32 step)
    {
        if (step == 0) return 0;
        if (step == 1) return (capacity - 1) & index_mask;
        return (random() % capacity) & index_mask;
    }

    void rebuild()
    {
        for (u32 i = 0; i != B::kTotalWords; ++i) bits.words[i] = 0;
        for (u32 i = 0; i != capacity; ++i)
        {
            if (expected[i])
                bits.words[i / B::kWordSize] |= Word{1} << (i % B::kWordSize);
        }
        for (u32 layer = 1; layer != B::kNumLayers; ++layer)
        {
            for (u32 i = 0; i != B::kLayersSizes[layer - 1]; ++i)
            {
                if (bits.words[B::offsets[layer - 1] + i])
                {
                    bits.words[B::offsets[layer] + i / B::kWordSize] |=
                        Word{1} << (i % B::kWordSize);
                }
            }
        }
    }

    void expect_valid()
    {
        EXPECT_EQ(storage[0], 73);
        EXPECT_EQ(storage[B::kTotalWords + 1], 91);
        for (u32 i = 0; i != capacity; ++i)
        {
            EXPECT_EQ(
                bool(
                    bits.words[i / B::kWordSize] &
                    (Word{1} << (i % B::kWordSize))),
                expected[i])
                << i;
        }
        for (u32 layer = 0; layer != B::kNumLayers; ++layer)
        {
            const u32 count =
                (layer == 0 ? capacity : B::kLayersSizes[layer - 1]) & ~u32{};
            for (u32 i = 0; i != B::kLayersSizes[layer] * B::kWordSize; ++i)
            {
                bool want = false;
                if (i < count)
                {
                    if (layer == 0)
                        want = expected[i];
                    else
                        want = bits.words[B::offsets[layer - 1] + i] != 0;
                }
                EXPECT_EQ(
                    bool(
                        bits.words[B::offsets[layer] + i / B::kWordSize] &
                        (Word{1} << (i % B::kWordSize))),
                    want)
                    << layer << ':' << i;
            }
        }
    }
};

using PbsTypes = ::testing::Types<
    PyramidBitset<1, u8>,
    PyramidBitset<7, u8>,
    PyramidBitset<8, u8>,
    PyramidBitset<9, u8>,
    PyramidBitset<63, u8>,
    PyramidBitset<64, u8>,
    PyramidBitset<65, u8>,
    PyramidBitset<512, u8>,
    PyramidBitset<513, u8>,
    PyramidBitset<15, u16>,
    PyramidBitset<16, u16>,
    PyramidBitset<17, u16>,
    PyramidBitset<255, u16>,
    PyramidBitset<256, u16>,
    PyramidBitset<257, u16>,
    PyramidBitset<31, u32>,
    PyramidBitset<32, u32>,
    PyramidBitset<33, u32>,
    PyramidBitset<1024, u32>,
    PyramidBitset<1025, u32>,
    PyramidBitset<1, u64>,
    PyramidBitset<63, u64>,
    PyramidBitset<64, u64>,
    PyramidBitset<65, u64>,
    PyramidBitset<4095, u64>,
    PyramidBitset<4096, u64>,
    PyramidBitset<4097, u64>,
    PyramidBitset<65536, u64>,
    PyramidBitset<100000, u64>>;
