#pragma once

#include <unordered_set>

#include "bump_allocator.hpp"

template <
    typename Value,
    typename Storage,
    typename Hash = std::hash<Value>,
    typename Cmp = std::equal_to<Value>>
using BumpHashSet =
    std::unordered_set<Value, Hash, Cmp, BumpAllocator<Value, Storage>>;
