#include <algorithm>
#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

struct ModInt
{
    inline static constexpr u32 kMOD = 1'000'000'007;
    [[gnu::always_inline]] constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept
    {
        value += rhs.value;
        value -= kMOD & -u32{value >= kMOD};
        return *this;
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
        const ModInt& rhs) const noexcept
    {
        u64 v = u64{value} * rhs.value;
        if (v >= kMOD) v %= kMOD;
        return ModInt{static_cast<u32>(v)};
    }

    u32 value = 0;
};

class Solution
{
public:
    [[gnu::target("avx2,bmi2")]]
    u32 maxSum(const std::vector<int>& nums, u32 k) const noexcept
    {
        u32 f[32]{};
        for (u32 v : reinterpret_cast<const std::vector<u32>&>(nums))
        {
            while (v)
            {
                int j = std::countr_zero(v);
                ++f[j];
                v &= ~(1u << j);
            }
        }

        u32 sorted[32];
        ModInt a{}, m{};
        for (u32 i = 0; i != 32; ++i)
        {
            sorted[i] = i;
            m.value |= (u32{!!f[i]} << i);
        }

        std::ranges::sort(sorted, std::less{}, [&](u32 bit) { return f[bit]; });

        for (u32 t{}; u32 bit : sorted)
        {
            u32 cnt = std::min(f[bit] - t, k);
            a += m * m * ModInt{cnt};
            k -= cnt;
            m.value &= ~(1u << bit);
            t += cnt;
        }

        return a.value;
    }
};
