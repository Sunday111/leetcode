#pragma once

#include <array>
#include <bit>
#include <concepts>

#include "ceil_div.hpp"
#include "int_if.hpp"

struct DefaultBitsetTraits
{
    using Word = uint64_t;
    static constexpr bool branchless = true;
};

template <auto size, auto traits = DefaultBitsetTraits{}>
    requires(std::unsigned_integral<decltype(size)>)
class Bitset
{
public:
    using Traits = decltype(traits);
    using Size = decltype(size);
    using Index = Size;
    using Word = typename Traits::Word;
    using Mask = Word;
    static constexpr Size word_bits = sizeof(Word) * 8;
    static constexpr Size num_words = ceil_div(size, word_bits);

    constexpr void Set(Index i, bool value) noexcept
    {
        Index word_index = i / word_bits;
        Index bit_index = i % word_bits;
        auto& word = words[word_index];
        if constexpr (traits.branchless)
        {
            Word a = (Mask{1} << bit_index) | word;
            Word b = (~(Mask{1} << bit_index)) & word;
            word = iif(value, a, b);
        }
        else
        {
            if (value)
            {
                Mask mask = Mask{1} << bit_index;
                word |= mask;
            }
            else
            {
                Mask mask = ~(Mask{1} << bit_index);
                word &= mask;
            }
        }
    }

    [[nodiscard]] constexpr bool Get(Index i) const noexcept
    {
        Index word_index = i / word_bits;
        Index bit_index = i % word_bits;
        auto& word = words[word_index];
        Mask mask = Mask{1} << bit_index;
        return word & mask;
    }

    constexpr void Flip() noexcept
    {
        for (auto& word : words) word = ~word;
    }

    [[nodiscard]] constexpr Bitset Flipped() const noexcept
    {
        auto copy = *this;
        copy.Flip();
        return copy;
    }

    void InplaceAnd(const Bitset& another) noexcept
    {
        for (Index word_index = 0; word_index != num_words; ++word_index)
        {
            words[word_index] &= another.words[word_index];
        }
    }

    [[nodiscard]] constexpr Bitset And(const Bitset& another) const noexcept
    {
        auto copy = *this;
        copy.InplaceAnd(another);
        return copy;
    }

    [[nodiscard]] constexpr Size Count() const noexcept
    {
        Size r = 0;
        for (auto& w : words) r += std::popcount(w);
        return r;
    }

    std::array<Word, num_words> words{};
};
