#include <algorithm>
#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>






template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};




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
    using u32 = uint32_t;
    u32 getMinDistance(std::vector<int>& nums, int target, u32 start)
    {
        u32 n = cast<u32>(nums.size()), r = n;
        for (u32 i = 0; i != n; ++i)
        {
            upd_min(
                r,
                iif(nums[i] == target,
                    (std::max(i, start) - std::min(i, start)),
                    n));
        }
        return r;
    }
};
