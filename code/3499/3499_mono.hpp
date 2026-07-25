#include <cstdint>
#include <string>




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

class Solution
{
public:
    [[nodiscard, gnu::target("bmi2,avx2")]]
    constexpr u32 maxActiveSectionsAfterTrade(const std::string& s) noexcept
    {
        u32 t = 0, r = 0, pz = 0;
        auto i = s.data(), e = i + s.size();
        while (i != e)
        {
            auto j = std::find(i, e, '0');
            auto k = std::find(j, e, '1');
            u32 z = static_cast<u32>(k - j);
            r = std::max(r, (z + pz) & -u32{z && pz});
            t += j - i;
            pz = z;
            i = k;
        }

        return r + t;
    }
};
