#include <algorithm>
#include <bit>
#include <cassert>
#include <functional>
#include <print>
#include <span>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>







inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

using u32 = uint32_t;

inline static constexpr u32 xxx = ~u32{};

struct Interval
{
    u32 begin{xxx};
    u32 end{xxx};
    u32 incl{}, excl{};
    bool is_leaf = true;

    [[nodiscard]] constexpr bool intersects(const Interval& b) const noexcept
    {
        return (end > b.begin) & (begin < b.end);
    }

    [[nodiscard]] constexpr bool contains(const Interval& b) const noexcept
    {
        return (begin < b.begin) & (end > b.end);
    }
    [[nodiscard]] constexpr bool contains(u32 i) const noexcept
    {
        return (begin <= i) & (end > i);
    }

    [[nodiscard]] constexpr bool is_empty() const noexcept
    {
        return begin == end;
    }

    [[nodiscard]] constexpr auto proj() const noexcept
    {
        return std::tuple{begin, end};
    }

    [[nodiscard]] constexpr auto merged_with(Interval x) const noexcept
    {
        upd_min(x.begin, begin);
        upd_max(x.end, end);
        x.excl |= excl;
        x.incl |= incl;
        x.incl |= x.excl;
        return x;
    }

    [[nodiscard]] constexpr bool operator==(const Interval&) const noexcept =
        default;
};

template <typename T, typename V, typename P = std::identity>
[[gnu::always_inline]] constexpr void
inplace_remove(std::span<T>& x, const V& value, P&& p = {}) noexcept
{
    x = std::span{
        std::begin(x),
        std::begin(std::ranges::remove(x, value, std::forward<P>(p)))};
}
template <typename T, typename P = std::identity>
[[gnu::always_inline]] constexpr void inplace_unique(
    std::span<T>& x,
    P&& p = {}) noexcept
{
    x = std::span{
        std::begin(x),
        std::begin(
            std::ranges::unique(x, std::equal_to{}, std::forward<P>(p)))};
}

class Solution
{
public:
    auto maxNumOfSubstrings(std::string_view str) noexcept
    {
        const auto s = str.data();
        const u32 n = str.size() & xxx;

        Interval buf[26]{};

        std::span<Interval> intervals{buf};

        // Find intervals
        for (u32 i = 0; i != n; ++i)
        {
            auto& interval = intervals[(s[i] - 'a') & 31];
            upd_min(interval.begin, i);
            interval.end = i + 1;
        }

        inplace_remove(intervals, xxx, &Interval::begin);
        std::ranges::sort(intervals, std::less{}, &Interval::proj);

        // Collect inclusive and exclusive characters for each interval
        for (auto& x : intervals)
        {
            for (u32 i = x.begin; i != x.end; ++i)
            {
                x.incl |= (1u << ((s[i] - 'a') & 31));
            }

            u32 next = x.begin;
            for (const auto& y : intervals)
            {
                if (y.begin >= x.end) break;
                if (x.contains(y))
                {
                    for (; next < y.begin; ++next)
                    {
                        x.excl |= (1u << ((s[next] - 'a') & 31));
                    }
                    upd_max(next, y.end);
                }
            }
            for (; next < x.end; ++next)
            {
                x.excl |= (1u << ((s[next] - 'a') & 31));
            }
        }

        auto print_intervals = [&]([[maybe_unused]] std::string_view label)
        {
            // auto chars = [](u32 mask)
            // {
            //     std::string out;
            //     for (u32 i = 0; i != 26; ++i)
            //     {
            //         if (mask & (1u << i)) out += static_cast<char>('a' + i);
            //     }
            //     return out;
            // };
            // std::println("{}:", label);
            // for (const auto& x : intervals)
            // {
            //     std::println(
            //         "[{}, {}) \"{}\" incl={{{}}} excl={{{}}}",
            //         x.begin,
            //         x.end,
            //         str.substr(x.begin, x.end - x.begin),
            //         chars(x.incl),
            //         chars(x.excl));
            // }
        };

        print_intervals("Before merging intervals");

        // Merge intervals with partial overlap
        for (auto& a : intervals)
        {
            for (auto& b : intervals)
            {
                if (a.intersects(b))
                {
                    if (a.contains(b))
                    {
                        a.incl |= b.incl | b.excl;
                    }
                    else if (b.contains(a))
                    {
                        b.incl |= a.incl | a.excl;
                    }
                    else
                    {
                        a = a.merged_with(b);
                        b = a;
                    }
                }
            }
        }

        // Remove possible duplicates after the merge
        std::ranges::sort(intervals, std::less{}, &Interval::proj);
        inplace_unique(intervals);

        print_intervals("Before building graph");

        // Build a graph
        {
            std::vector<Interval*> open;
            auto it = std::begin(intervals);

            auto close_intervals = [&](u32 i)
            {
                while (!open.empty() && open.back()->end <= i)
                {
                    auto& x = *open.back();
                    open.pop_back();
                    if (!open.empty() && open.back()->contains(x))
                    {
                        bool must_merge = false;
                        for (auto& p : open)
                        {
                            if (p->excl & x.incl)
                            {
                                must_merge = true;
                                break;
                            }
                        }

                        auto parent = open.back();
                        if (must_merge)
                        {
                            bool is_leaf = parent->is_leaf && x.is_leaf;
                            *parent = parent->merged_with(x);
                            parent->is_leaf = is_leaf;
                            x = {};
                        }
                        else
                        {
                            parent->incl |= x.incl;
                            parent->is_leaf = false;
                        }
                    }
                }
            };

            for (u32 i = 0; i != n; ++i)
            {
                close_intervals(i);
                if (std::end(intervals) != it && it->begin == i)
                {
                    open.push_back(&*(it++));
                }
            }
            close_intervals(n);
        }

        std::vector<std::string> out;
        for (auto& x : intervals)
        {
            if (!x.is_empty() && x.is_leaf)
            {
                out.emplace_back(str.substr(x.begin, x.end - x.begin));
            }
        }

        return out;
    }
};
