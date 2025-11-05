#pragma once

#include <set>

#include "bump_allocator.hpp"

template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpSet = std::set<V, Cmp, BumpAllocator<V, Storage>>;
