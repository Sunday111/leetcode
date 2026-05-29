#include <cstdint>
#include <ranges>
#include <utility>
#include <vector>






template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

template <typename To>
inline static constexpr auto cast_view = std::views::transform(cast<To>);


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    u32 minElement(std::vector<int>& nums)
    {
        u32 r = 9 * 4;

        for (u32 x : nums | cast_view<u32>)
        {
            u32 s = x % 10 + (x / 10) % 10 + (x / 100) % 10 + (x / 1000) % 10;
            r = std::min(r, s);
        }

        return std::max(r, 1u);
    }
};
