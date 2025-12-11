#include "aoc_2025_11.hpp"

namespace part1
{

class Solution
{
public:
    inline static constexpr auto as_sview = [](auto l)
    {
        return std::string_view{l};
    };

    template <char pattern>
    inline static constexpr auto split_filter =
        stdv::split(pattern) | stdv::filter(stdr::size) |
        stdv::transform(as_sview);

    static Line parse_line(std::string_view s)
    {
        u32 i = 0;
        while (s[i] != ':') ++i;
        return {
            .parent = s.substr(0, i),
            .children =
                stdr::to<std::vector>(s.substr(i + 1) | split_filter<' '>),
        };
    }

    Map<std::string_view, Set<std::string_view>> g;
    Map<std::string_view, u64> memo;
    Set<std::string_view> visited;
    std::vector<std::string_view> q;

    u64 dfs(std::string_view from) noexcept
    {
        if (from == "out") return 1;

        u64* r{};
        {
            auto [it, added] = memo.try_emplace(from);
            if (!added) return it->second;
            r = &it->second;
        }

        for (auto c : g[from])
        {
            *r += dfs(c);
        }

        return *r;
    }

    u64 solve(std::string_view input_lines) noexcept
    {
        auto lines = stdr::to<std::vector>(
            input_lines | split_filter<'\n'> | stdv::transform(parse_line));

        for (auto line : lines)
        {
            g[line.parent].insert_range(line.children);
            logln("{}: {}", line.parent, line.children);
        }

        return dfs("you");
    }
};
}  // namespace part1
