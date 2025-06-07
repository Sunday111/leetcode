#pragma once

#include <array>
#include <string>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;

    template <typename T>
    static T& get_static_object()
    {
        static T obj;
        return obj;
    }

    [[nodiscard]] static std::string clearStars(std::string s) noexcept
    {
        size_t t = s.rfind('*');
        if (t == s.npos) return s;
        ++t;

        u32 n = s.size() & 0xFFFFFFFF;
        auto& removed = get_static_object<std::vector<bool>>();
        removed.reserve(100'000);
        removed.assign(removed.size(), false);
        removed.resize(n);

        constexpr auto kInvalidIndex = std::numeric_limits<u32>::max();

        std::array<u32, 26> last;  // NOLINT
        last.fill(kInvalidIndex);

        auto& prev = get_static_object<std::vector<u32>>();
        prev.reserve(100'000);
        prev.resize(n);

        u32 total = 0;
        for (u32 i = 0; i != t; ++i)
        {
            char c = s[i];
            if (c == '*')
            {
                removed[i] = true;

                if (total != 0)
                {
                    --total;
                    u8 min_idx = 0;
                    while (last[min_idx] == kInvalidIndex) ++min_idx;
                    auto l = last[min_idx];
                    removed[l] = true;
                    last[min_idx] = prev[l];
                }
            }
            else
            {
                u8 ci = (c - 'a') & 0xFF;
                prev[i] = last[ci];
                last[ci] = i;
                ++total;
            }
        }

        total += n - t;

        for (u32 out = 0, in = 0; out != total; ++in)
        {
            if (!removed[in]) s[out++] = s[in];
        }

        s.resize(total);

        return s;
    }
};
