#include <array>
#include <bit>
#include <format>
#include <string>
#include <vector>

#include "integral_aliases.hpp"

inline constexpr auto kNumEntries = []
{
    std::array<u16, 11> r{};

    for (u8 h = 0; h != 12; ++h)
    {
        u8 ph = std::popcount(h) & 0xF;
        for (u8 m = 0; m != 60; ++m)
        {
            u8 pm = std::popcount(m) & 0xF;
            u8 p = ph + pm;
            ++r[p];
        }
    }

    return r;
}();

inline constexpr auto kOffsets = []
{
    std::array<u16, 11> r{};

    u16 offset = 0;

    for (u8 i = 0; i != kNumEntries.size(); ++i)
    {
        r[i] = offset;
        offset += kNumEntries[i];
    }

    return r;
}();

inline constexpr auto kEntries = []
{
    auto offsets = kOffsets;

    // NOLINTNEXTLINE
    std::array<u16, 60 * 12> entries;

    for (u8 h = 0; h != 12; ++h)
    {
        u8 ph = std::popcount(h) & 0xF;
        for (u8 m = 0; m != 60; ++m)
        {
            u8 pm = std::popcount(m) & 0xF;
            u8 p = ph + pm;
            auto& offset = offsets[p];
            u16 x = h;
            x <<= 6;
            x |= m;
            entries[offset++] = x;
        }
    }

    return entries;
}();

class Solution
{
public:
    std::vector<std::string> readBinaryWatch(u8 turned_on) noexcept
    {
        std::vector<std::string> r;

        u16 num = kNumEntries[turned_on];
        r.reserve(num);

        for (u16 i = kOffsets[turned_on], end = i + num; i != end; ++i)
        {
            u16 x = kEntries[i];
            u16 m = x & 0b111111;
            u16 h = x >> 6;
            r.emplace_back(std::format("{}:{:02}", h, m));
        }

        return r;
    }
};
