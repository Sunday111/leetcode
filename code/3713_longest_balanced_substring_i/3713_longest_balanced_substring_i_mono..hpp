#include <array>
#include <concepts>
#include <cstdint>
#include <string>

#define HOT_PATH __attribute__((hot))

#define FORCE_INLINE inline __attribute__((always_inline))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

class Solution
{
public:
    using u16 = uint16_t;
    static u16 longestBalanced(const std::string& s) noexcept HOT_PATH
    {
        const u16 n = static_cast<u16>(s.size());

        std::array<u16, 26> freq{};
        u16 r = 0, min = 0, max = 0;
        for (u16 i = 0; i != n && r < n - i; ++i)
        {
            freq.fill(0);
            min = max = 1;
            for (u16 j = i; j != n && r < n - i; ++j)
            {
                u16& f = freq[(s[j] - 'a') & 0x1F];
                if (f++ <= min)
                {
                    min = f;
                    for (auto& v : freq)
                    {
                        min = iif(v && v < min, v, min);
                    }
                }

                max = std::max(max, f);

                u16 l = j + 1 - i;
                r = iif(min == max && l > r, l, r);
            }
        }

        return r;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
