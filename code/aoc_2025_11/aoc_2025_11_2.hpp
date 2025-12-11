#include "aoc_2025_11.hpp"

namespace part2
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
    Map<std::string, u64> memo;
    Set<std::string_view> visited;
    std::vector<std::string_view> q;

    u32 dac_counter = 0;
    u32 fft_counter = 0;

    std::vector<std::string_view> path;
    std::vector<std::vector<std::string_view>> paths;

    u64 dfs() noexcept
    {
        std::string_view src = path.back();

        if (src == "out")
        {
            if (dac_counter && fft_counter)
            {
                paths.push_back(path);
                logln(" ok path: {}", path);
                return 1;
            }

            logln("bad path: {}", path);
            return 0;
        }

        u64 rv = 0;
        u64* r = &rv;
        {
            std::string key =
                std::format("{}_{}_{}", dac_counter, fft_counter, src);

            auto [it, added] = memo.try_emplace(std::move(key));
            if (!added) return it->second;
            r = &it->second;
        }
        bool visit_dac = src == "dac", visit_fft = src == "fft";
        dac_counter += visit_dac, fft_counter += visit_fft;

        for (auto c : g[src])
        {
            path.push_back(c);
            *r += dfs();
            path.pop_back();
        }

        dac_counter -= visit_dac;
        fft_counter -= visit_fft;

        return *r;
    }

    u64 solve(std::string_view input_lines) noexcept
    {
        auto lines = stdr::to<std::vector>(
            input_lines | split_filter<'\n'> | stdv::transform(parse_line));

        for (auto line : lines)
        {
            g[line.parent].insert_range(line.children);
            logln("{} -> {}", line.parent, line.children);
        }

        path.push_back("svr");
        return dfs();
    }
};
}  // namespace part2
