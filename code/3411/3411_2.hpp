#include <cstdint>
#include <vector>

#include "solution_name.hpp"

using u32 = uint32_t;

class LC_SOLUTION_NAME(_2)
{
    inline static constexpr uint64_t gg = 0x52183412100ULL;

    static constexpr u32 g(int x) { return (gg >> (x << 2)) & 15u; }

public:
    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 maxLength(const std::vector<int>& nums) noexcept
    {
        const u32 n = nums.size() & ~u32{};
        const int *l = nums.data(), *r{l}, *e{l + n};
        u32 m1{}, a{2};

        while (r != e)
        {
            u32 m2 = g(*r++);
            while (m1 & m2) m1 &= ~g(*l++);
            m1 |= m2;
            u32 a2 = (r - l) & 127;
            a = a2 > a ? a2 : a;
        }

        return a;
    }
};
