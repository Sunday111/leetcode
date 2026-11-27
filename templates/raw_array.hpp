#pragma once

#include <cstddef>

template <typename T, std::size_t N>
struct RawArray
{
    T data[N];
};

template <typename T>
struct RawArray<T, 0>
{
};
