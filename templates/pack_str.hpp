#pragma once

#include <immintrin.h>

#include <string>

#include "cast.hpp"
#include "integral_aliases.hpp"

// NOLINTBEGIN
static constexpr u64 BIAS = 0x6060606060606060ull, EXT = 0x1F1F1F1F1F1F1F1Full;
inline u64 packStr(const std::string& s) noexcept
    __attribute__((hot, __target__("bmi2")))
{
    const char* c8 = s.c_str();
    u8 n8 = s.length() & 0xFF;
    u8 sh = 50;
    u64 r = 0;
    if (n8 >= 8)
    {
        const u64 qw = *reinterpret_cast<const u64*>(c8) - BIAS;
        sh -= 40;
        r += _pext_u64(__builtin_bswap64(qw), EXT) << sh;
        c8 += 8;
        n8 -= 8;
    }
    if (n8 >= 4)
    {
        const u32 dw = *reinterpret_cast<const u32*>(c8) - (BIAS & 0xFFFFFFFFu);
        sh -= 20;
        r += u64{_pext_u32(__builtin_bswap32(dw), EXT & 0xFFFFFFFFu)} << sh;
        c8 += 4;
        n8 -= 4;
    }
    if (n8 >= 2)
    {
        const u16 w = *reinterpret_cast<const u16*>(c8) - (BIAS & 0xFFFFu);
        sh -= 10;
        r += u64{_pext_u32(__builtin_bswap32(w) >> 16, EXT & 0xFFFFu)} << sh;
        c8 += 2;
        n8 -= 2;
    }
    if (n8)
    {
        sh -= 5;
        r += (cast<u64>(*c8) - (BIAS & 0xFFu)) << sh;
        c8 += 1;
        n8 -= 1;
    }
    return r;
}

inline std::string unpackStr(const u64 v) noexcept
    __attribute__((hot, __target__("bmi2")))
{
    std::string r(10, '\0');
    char* c8 = r.data();
    *reinterpret_cast<u64*>(c8) =
        __builtin_bswap64(_pdep_u64(v >> 10, EXT)) + BIAS;
    *reinterpret_cast<u16*>(c8 + 8u) =
        __builtin_bswap32(
            cast<u32>(_pdep_u32(cast<u32>(v), EXT & 0xFFFFu) + (BIAS & 0xFFFFu))
            << 16) &
        0xFFFF;
    const auto end = r.find(BIAS & 0xFFu);
    if (end != std::string::npos) r.resize(end);
    return r;
}
// NOLINTEND
