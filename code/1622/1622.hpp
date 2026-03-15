#include <array>

#include "mod_int.hpp"

class Fancy
{
    inline static ModInt nums[100000], mul{1}, add{0}, inv_mul{1};
    u32 n = 0;

public:
    inline static constexpr auto kPow = []
    {
        std::array<ModInt, 101> r;

        for (ModInt base{0}; base.value != r.size(); ++base.value)
        {
            r[base.value] = base.pow(kMOD - 2);
        }

        return r;
    }();

    void append(int v) noexcept
    {
        nums[n++] = (ModInt{static_cast<u32>(v)} - add) * inv_mul;
    }

    void addAll(int v) noexcept { add += {static_cast<u32>(v)}; }

    void multAll(int v) noexcept
    {
        ModInt x{static_cast<u32>(v)};
        mul *= x, add *= x;
        inv_mul *= kPow[x.value];
    }

    [[nodiscard]] int getIndex(int idx) const noexcept
    {
        u32 m = -u32{std::cmp_less(idx, n)};
        return static_cast<int>(((nums[idx] * mul + add).value + 1) & m) - 1;
    }
};

#include "sync_stdio.hpp"
