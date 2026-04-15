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

    inline static constexpr u32 kMaxVal = 1'000'000;
    inline static constexpr u32 kMaxN = 100'000;

    void impl(const std::vector<u32>& nums, std::vector<u32>& queries)
    {
        const auto n = cast<u32>(nums.size());
        [[assume(n <= kMaxN)]];

        constexpr u32 lim = 100'000;
        static u32 d[kMaxN + 1], p[kMaxVal + 1];

        [[maybe_unused]] static const auto _ = [&]
        {
            std::ranges::fill(p, lim);
            return ' ';
        }();

        for (u32 i = 0; i != n; ++i)
        {
            const auto v = nums[i];
            [[assume(v <= kMaxVal)]];
            auto& j = p[v];
            j = std::min(j, i);
            u32 x = iif(i == j, ~u32{}, i - j);
            d[i] = x;
            upd_min(d[j], x);
            j = i;
        }
        for (u32 i = 0; i != n; ++i)
        {
            const auto v = nums[i];
            [[assume(v <= kMaxVal)]];
            auto& j = p[v];
            u32 x = iif(j == lim, lim, n - j + i);
            upd_min(d[i], x);
            upd_min(d[j], x);
            j = lim;
        }

        for (auto& i : queries)
        {
            i = iif(d[i] == 0 || d[i] == n, ~u32{}, d[i]);
        }
    }
    std::vector<int> solveQueries(
        std::vector<int>& nums,
        std::vector<int>& queries)
    {
        impl(
            reinterpret_cast<std::vector<u32>&>(nums),
            reinterpret_cast<std::vector<u32>&>(queries));
        return std::move(queries);
    }
};
