#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory_resource>
#include <unordered_map>
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




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

class Solution
{
public:
    inline static std::pmr::unsynchronized_pool_resource pool;

    [[nodiscard, gnu::always_inline]] static constexpr u32 reverse(
        u32 x) noexcept
    {
        u32 r = 0;
        while (x)
        {
            r = r * 10 + x % 10;
            x /= 10;
        }
        return r;
    }
    [[nodiscard]] static u32 impl(std::vector<u32>& nums) noexcept
    {
        std::pmr::unordered_map<u32, u32> m(&pool);
        u32 n = cast<u32>(nums.size()), r = n;
        m.reserve(2 * n);
        for (u32 i = 0; i != n; ++i)
        {
            u32 v = nums[i];
            if (auto it = m.find(v); it != m.end())
            {
                upd_min(r, i - it->second);
            }
            m[reverse(v)] = i;
        }
        return r == n ? ~u32{} : r;
    }

    int minMirrorPairDistance(std::vector<int>& nums) const noexcept
    {
        return std::bit_cast<int>(
            impl(reinterpret_cast<std::vector<u32>&>(nums)));
    }
};
