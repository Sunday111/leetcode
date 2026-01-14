#pragma once

#include <map>

#include "bump_allocator.hpp"

template <typename K, typename V, typename Storage, typename Cmp = std::less<K>>
using BumpMap =
    std::map<K, V, Cmp, BumpAllocator<std::pair<const K, V>, Storage>>;
