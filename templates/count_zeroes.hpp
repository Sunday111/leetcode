#pragma once

#include "integral_aliases.hpp"

u64 count_numbers_with_zeroes(u64 n)
{
    if (n <= 0) return 0;

    // convert n to digits (no allocations)
    u32 digits[20];
    u32 len = 0;
    u64 tmp = n;
    while (tmp)
    {
        digits[len++] = tmp % 10;
        tmp /= 10;
    }
    // digits[] is reversed: least significant first
    // we’ll process from most significant
    u64 num_no_zero = 0;

    // precompute powers of 9
    u64 pow9[20];
    pow9[0] = 1;
    for (u32 i = 1; i < 20; ++i) pow9[i] = pow9[i - 1] * 9;

    // count numbers with fewer digits
    for (u32 k = 1; k < len; ++k) num_no_zero += pow9[k];

    // count numbers with same length
    for (u32 i = len; i--;)
    {
        u32 d = digits[i];
        u32 pos = i;  // number of remaining digits after this
        if (d == 0) break;
        num_no_zero += (d - 1) * pow9[pos];
        if (i == 0) num_no_zero += 1;  // n itself has no zero
    }

    return n - num_no_zero;
}
