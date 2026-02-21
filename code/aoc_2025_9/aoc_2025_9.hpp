#include <algorithm>
#include <atomic>
#include <cassert>
#include <cstdlib>
// #include <print>
#include <ranges>
#include <span>
#include <thread>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"
#include "swap_if_greater.hpp"

template <std::integral T>
struct Vec2
{
    T x, y;

    template <std::integral To>
    [[nodiscard]] constexpr Vec2<To> cast() const noexcept
    {
        return Vec2<To>{::cast<To>(x), ::cast<To>(y)};
    }

    [[nodiscard]] bool operator==(const Vec2& v) const noexcept = default;
    [[nodiscard]] bool operator!=(const Vec2& v) const noexcept = default;
};

template <std::integral T>
inline constexpr Vec2<T> add(Vec2<T> a, Vec2<T> b) noexcept
{
    return {a.x + b.x, a.y + b.y};
}

template <std::integral T>
inline constexpr Vec2<T> add(Vec2<T> a, T b) noexcept
{
    return add(a, Vec2{b, b});
}

template <std::integral T>
inline constexpr Vec2<T> sub(Vec2<T> a, Vec2<T> b) noexcept
{
    return {a.x - b.x, a.y - b.y};
}

template <std::signed_integral T>
inline constexpr Vec2<T> abs(Vec2<T> v) noexcept
{
    return {std::abs(v.x), std::abs(v.y)};
}

namespace stdr = std::ranges;
namespace stdv = std::views;

class Solution1
{
public:
    static u64 solve(std::span<const Vec2<u32>> points) noexcept
    {
        const auto n = cast<u32>(points.size());

        u64 max_area = 0;
        // u32 a = 0, b = 0;
        for (const auto i : stdv::iota(0u, n))
        {
            for (const auto j : stdv::iota(i + 1, n))
            {
                auto v =
                    add(abs(sub(points[i].cast<i32>(), points[j].cast<i32>())),
                        1)
                        .cast<u64>();
                u64 area = v.x * v.y;
                if (area > max_area)
                {
                    max_area = area;
                    // a = i;
                    // b = j;
                }
            }
        }

        // std::println(
        //     "[{},{}], [{},{}] -> {}",
        //     points[a].x,
        //     points[a].y,
        //     points[b].x,
        //     points[b].y,
        //     max_area);

        return max_area;
    }
};

class Solution2
{
public:
    using Vec2u = Vec2<u32>;
    static u64 solve(std::span<const Vec2<u32>> points) noexcept
    {
        auto [minx, maxx] =
            stdr::minmax(points | stdv::transform(&Vec2<u32>::x));
        // std::println("x: [{}, {}]", minx, maxx);

        auto [miny, maxy] =
            stdr::minmax(points | stdv::transform(&Vec2<u32>::y));
        // std::println("y: [{}, {}]", miny, maxy);

        const auto grid_extent = Vec2{maxx + 2, maxy + 2}.cast<size_t>();
        std::vector<u8> grid(grid_extent.x * grid_extent.y, 0);

        constexpr u8 kInner = 2;
        constexpr u8 kOut = 1;

        auto to_index = [&](Vec2u p) -> size_t
        {
            u64 idx = size_t{p.y} * grid_extent.x + size_t{p.x};
            assert(idx < grid.size());
            return idx;
        };

        auto get_cell = [&](Vec2u p) -> u8&
        {
            return grid[to_index(p)];
        };

        // std::println("Marking walls...");
        const auto n = cast<u32>(points.size());
        for (auto start_point_index : stdv::iota(0u, n))
        {
            u32 finish_point_index = (start_point_index + 1) % n;
            Vec2u start_point = points[start_point_index];
            Vec2u finish_point = points[finish_point_index];
            bool same_x = start_point.x == finish_point.x;
            bool same_y = start_point.y == finish_point.y;
            assert(same_x || same_y);
            swap_if_greater(start_point.x, finish_point.x);
            swap_if_greater(start_point.y, finish_point.y);
            Vec2u step{same_y, same_x};
            while (start_point != finish_point)
            {
                get_cell(start_point) = kInner;
                start_point = add(start_point, step);
            }
        }

        {
            // std::println("Marking outer space");
            std::vector<Vec2u> q;
            q.reserve(190000000);
            q.push_back(Vec2u{0, 0});
            while (!q.empty())
            {
                auto p = q.back();
                q.pop_back();

                u8& cell = get_cell(p);
                if (cell != 0) continue;
                cell = kOut;

                auto left = Vec2{p.x - 1, p.y};
                if (left.x < grid_extent.x && !get_cell(left))
                {
                    q.push_back(left);
                }

                auto right = Vec2{p.x + 1, p.y};
                if (right.x != grid_extent.x && !get_cell(right))
                {
                    q.push_back(right);
                }

                auto up = Vec2{p.x, p.y + 1};
                if (up.y != grid_extent.y && !get_cell(up))
                {
                    q.push_back(up);
                }

                auto down = Vec2{p.x, p.y - 1};
                if (down.y < grid_extent.y && !get_cell(down))
                {
                    q.push_back(down);
                }
            }

            // std::println("queue cap: {}", q.capacity());
        }

        constexpr u8 kCorner = 4;
        for (auto start_pt : points)
        {
            get_cell(start_pt) = kCorner;
        }

        std::atomic<u64> max_area = 0;

        auto handle_point = [&](Vec2u start_pt)
        {
            u32 max_w = 1;

            {
                Vec2 pt = add(start_pt, {1, 0});
                u8 ptc = get_cell(pt);
                while (ptc != kOut)
                {
                    ++pt.x;
                    if (ptc == kCorner)
                    {
                        max_area = std::max<u64>(max_area, pt.x - start_pt.x);
                    }
                    ptc = get_cell(pt);
                }
                max_w = pt.x - start_pt.x;
            }

            auto test_row = [&](Vec2u rb)
            {
                for (u32 offset_x = 0; offset_x != max_w; ++offset_x)
                {
                    Vec2 pt = add(rb, {offset_x, 0});
                    switch (get_cell(pt))
                    {
                    case kOut:
                        max_w = offset_x + 1;
                        break;
                    case kCorner:
                    {
                        u32 w = offset_x + 1;
                        u32 h = cast<u32>(std::abs(
                                    cast<int>(rb.y) - cast<int>(start_pt.y))) +
                                1;
                        u64 area = u64{w} * u64{h};

                        if (area > max_area)
                        {
                            // std::println(
                            //     "    {},{} - {},{}: {}",
                            //     start_pt.x,
                            //     start_pt.y,
                            //     start_pt.x + w - 1,
                            //     start_pt.y + h - 1,
                            //     area);
                        }

                        auto old = max_area.load(std::memory_order_relaxed);
                        while (area > old && !max_area.compare_exchange_weak(
                                                 old,
                                                 area,
                                                 std::memory_order_acq_rel,
                                                 std::memory_order_relaxed))
                        {
                        }
                    }
                    break;
                    }
                }
            };

            // up
            Vec2u rb = add(start_pt, {0, 1});
            while (get_cell(rb) != kOut)
            {
                test_row(rb);
                ++rb.y;
            }

            // down
            rb = start_pt;
            --rb.y;
            while (get_cell(rb) != kOut)
            {
                test_row(rb);
                --rb.y;
            }
        };

        constexpr u32 num_threads = 16u;
        std::vector<std::atomic<bool>> jobs(n);
        std::vector<std::thread> threads;
        for (u32 thread_index = 0; thread_index != num_threads; ++thread_index)
        {
            threads.emplace_back(
                [&]()
                {
                    for (u32 i = 0; i != n; ++i)
                    {
                        auto& j = jobs[i];
                        bool old = false;
                        if (!j.compare_exchange_strong(old, true))
                        {
                            continue;
                        }

                        handle_point(points[i]);
                    }
                });
        }

        for (auto& t : threads) t.join();
        return max_area;
    }
};
