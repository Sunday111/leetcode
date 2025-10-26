#include <algorithm>
#include <array>
#include <span>
#include <string>

template <int n>
struct HS
{
    inline static constexpr auto a = []
    {
        if constexpr (n == 0)
        {
            return std::array<std::array<char, 0>, 0>{};
        }
        else if constexpr (n == 1)
        {
            return std::array<std::array<char, 1>, 3>{{{'a'}, {'b'}, {'c'}}};
        }
        else
        {
            std::array<std::array<char, n>, 3 * (1 << (n - 1))> r{};
            size_t i = 0;
            for (auto& ps : HS<n - 1>::a)
            {
                for (char c : {'a', 'b', 'c'})
                {
                    if (ps.back() != c)
                    {
                        auto& s = r[i++];
                        std::copy_n(ps.begin(), n - 1, s.begin());
                        s.back() = c;
                    }
                }
            }
            return r;
        };
    }();
};

template <int n>
inline constexpr auto kArr = []
{
    constexpr auto& src = HS<n>::a;
    std::array<std::string_view, src.size()> r{};
    size_t i = 0;
    for (auto& s : src) r[i++] = {s.data(), n};
    return r;
}();

inline static constexpr auto kArrs = []
{
    using SpanView = std::span<const std::string_view>;
    return []<size_t... idx>(std::index_sequence<idx...>)
    {
        return std::array<SpanView, sizeof...(idx)>{{kArr<idx>...}};
    }(std::make_index_sequence<11>());
}();

class Solution
{
public:
    static constexpr std::string getHappyString(size_t n, size_t k) noexcept
    {
        auto& a = kArrs[n];
        if (--k < a.size()) return std::string(a[k]);
        return "";
    }
};
