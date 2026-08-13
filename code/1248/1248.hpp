#include <vector>

using u32 = uint32_t;

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] static constexpr u32
    find_odd(const u32* p, u32 i, u32 n)
    {
        while (i != n && !(p[i] & 1)) ++i;
        return i;
    }

    [[nodiscard]] inline static constexpr auto
    impl(const u32* a, u32 n, u32 k) noexcept
    {
        u32 i = 0, j = find_odd(a, 0, n), h = j + 1;

        // collect first k odd values
        while (j != n && k)
        {
            k -= a[j++] & 1;
        }

        u32 x = h & -u32{!k};
        while (j != n)
        {
            if (a[j++] & 1)
            {
                i += h;
                h = find_odd(a, i, n) - i + 1u;
            }
            x += h;
        }

        return x;
    }
    [[nodiscard]] u32 numberOfSubarrays(std::vector<int>& nums, u32 k) noexcept
    {
        return impl(
            reinterpret_cast<const u32*>(nums.data()),
            static_cast<u32>(nums.size()),
            k);
    }
};
