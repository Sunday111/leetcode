#pragma once

#include <vector>

#include "bump_allocator.hpp"

template <typename Value, typename Storage>
using BumpVector = std::vector<Value, BumpAllocator<Value, Storage>>;
