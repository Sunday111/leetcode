#include <algorithm>
#include <functional>
#include <string>
#include <utility>
#include <vector>




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
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
    int closestTarget(std::vector<std::string>& w, std::string& t, int s)
        const noexcept
    {
        int n = cast<int>(w.size()), r = n;
        auto d = w.data();
        auto u = std::bind(upd_min, r, std::placeholders::_1);
        for (int i = 0; i != n; ++i)
        {
            if (d[i] == t)
            {
                int k = i - s;
                u(std::abs(k));
                u(std::abs(n - k));
                u(std::abs(n + k));
            }
        }
        return r == n ? -1 : r;
    }
};
