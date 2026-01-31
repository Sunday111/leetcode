#pragma once

#include <set>

#include "bump_allocator.hpp"

template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpMultiset = std::multiset<V, Cmp, BumpAllocator<V, Storage>>;
