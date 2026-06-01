#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    u32 minimumCost(std::vector<int>& cost)
    {
        std::ranges::sort(cost);
        u32 n = cast<u32>(cost.size()), k = n % 3, s = 0;
        auto c = reinterpret_cast<const u32*>(cost.data());
        for (u32 i = n; i != k; --i)
        {
            s += c[--i];
            s += c[--i];
        }
        for (u32 i = k; i--;)
        {
            s += c[i];
        }
        return s;
    }
};
