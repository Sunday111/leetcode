#pragma once

#include <cstddef>
#include <span>

#include "bitsets/bitset_word.hpp"

template <BitsetWord Word, std::size_t extent = std::dynamic_extent>
struct BitsetView
{
    Word* words;
    static constexpr std::size_t capacity = extent;
};

template <BitsetWord Word>
struct BitsetView<Word, std::dynamic_extent>
{
    Word* words;
    std::size_t capacity;
};
