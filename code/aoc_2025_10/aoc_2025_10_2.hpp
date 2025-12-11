
#include <unordered_set>

#include "aoc_2025_10.hpp"

template <
    typename Key,
    typename Value,
    typename Hasher = std::hash<Key>,
    typename Cmp = std::equal_to<Key>,
    typename Allocator = std::allocator<std::pair<const Key, Value>>>
using Map = std::unordered_map<Key, Value, Hasher, Cmp, Allocator>;

template <
    typename Value,
    typename Hasher = std::hash<Value>,
    typename Cmp = std::equal_to<Value>,
    typename Allocator = std::allocator<Value>>
using Set = std::unordered_set<Value, Hasher, Cmp, Allocator>;

namespace part2
{

struct Machine
{
    u32 target_state = 0;
    std::vector<std::vector<u32>> buttons;
    std::vector<u32> counters;
};

struct RecursiveSolver
{
    struct State
    {
        std::array<u16, 10> counters{};
        u8 button_index = 0;

        constexpr bool operator==(const State&) const noexcept = default;
    };

    struct Hasher
    {
        size_t operator()(const State& s) const noexcept
        {
            u64 a = (u64{s.counters[0]} << 48) | (u64{s.counters[1]} << 32) |
                    (u64{s.counters[2]} << 16) | (u64{s.counters[3]} << 00);
            u64 b = (u64{s.counters[4]} << 48) | (u64{s.counters[5]} << 32) |
                    (u64{s.counters[6]} << 16) | (u64{s.counters[7]} << 00);
            u64 c = (u64{s.button_index} << 32) | (u64{s.counters[8]} << 16) |
                    (u64{s.counters[9]} << 00);

            constexpr std::hash<u64> h{};

            return (h(c) << 2) ^ (h(b) << 1) ^ h(a);
        }
    };

    std::vector<std::vector<u32>> buttons{};
    std::unordered_map<State, u64, Hasher> memo{};
    State state{};

    u64 solve()
    {
        constexpr u32 kNoSolution = 3000;

        if (state.button_index == buttons.size())
        {
            if (stdr::max(state.counters))
            {
                return kNoSolution;
            }

            return 0;
        }

        u64* r{};
        {
            auto [it, added] = memo.try_emplace(state, kNoSolution);
            if (!added) return it->second;
            r = &(it->second);
        }

        auto& button_counters = buttons[state.button_index];
        auto saved_state = state;

        ++state.button_index;

        const u32 btn_lim = stdr::min(
            button_counters |
            stdv::transform([&](u32 counter_idx)
                            { return state.counters[counter_idx]; }));

        *r = solve();
        if (state.button_index == 1) logln("    0/{}", btn_lim);

        for (u32 presses = 1; presses <= btn_lim; ++presses)
        {
            for (u32 counter_index : button_counters)
            {
                state.counters[counter_index]--;
            }

            *r = std::min(*r, presses + solve());
            if (state.button_index == 1) logln("    {}/{}", presses, btn_lim);
        }

        state = saved_state;

        return *r;
    }

    static u64 min_presses(Machine machine)
    {
        RecursiveSolver solver;
        for (u32 i = 0; i != machine.counters.size(); ++i)
        {
            solver.state.counters[i] = machine.counters[i] & 0xFFFF;
        }

        Map<u32, Set<u32>> buttons;
        for (u32 i = 0; i != machine.buttons.size(); ++i)
        {
            buttons[i].insert_range(machine.buttons[i]);
        }

        u64 exclusive_presses = 0;
        for (bool changes = true; std::exchange(changes, false);)
        {
            for (auto i = buttons.begin(); i != buttons.end();)
            {
                auto unique = i->second;
                for (auto& [idx, counters] : buttons)
                {
                    if (idx == i->first) continue;
                    for (auto x : counters)
                    {
                        unique.erase(x);
                    }
                }

                if (unique.empty())
                {
                    ++i;
                }
                else
                {
                    auto unique_counter = *(unique.begin());
                    auto presses = solver.state.counters[unique_counter];
                    for (u32 x : i->second) solver.state.counters[x] -= presses;
                    i = buttons.erase(i);
                    changes = true;
                    exclusive_presses += presses;
                }
            }
        }
        stdr::sort(
            solver.buttons,
            std::less{},
            [&](auto& btn)
            {
                u16 min_counter = 300;
                for (u32 counter_index : btn)
                {
                    min_counter = std::min<u16>(
                        solver.state.counters[counter_index],
                        min_counter);
                }

                return min_counter;
            });

        logln("    exclusive presses: {}", exclusive_presses);
        for (auto& [idx, counters] : buttons)
        {
            solver.buttons.emplace_back().append_range(counters);
        }
        logln("    non-exclusive buttons: {}", solver.buttons);

        {
            auto start = Clock::now();
            solver.memo.reserve(100'000'000);
            auto finish = Clock::now();
            logln(
                "    Reserve time: {}",
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    finish - start));
        }

        return exclusive_presses + solver.solve();
    }
};

class Solution
{
public:
    static Machine parse_spec(std::string_view s)
    {
        const u32 l = cast<u32>(s.size());
        u32 i = 0;
        auto consume = [&]([[maybe_unused]] char c)
        {
            assert(i != l);
            assert(s[i] == c);
            ++i;
        };
        auto try_consume = [&](char c)
        {
            bool b = i != l && s[i] == c;
            i += b;
            return b;
        };

        auto parse_uint = [&]
        {
            assert(std::isdigit(s[i]));
            u32 r = (s[i++] - '0') & 0xF;
            char c = s[i];
            while (std::isdigit(c))
            {
                r *= 10;
                r += (c - '0') & 0xF;
                c = s[++i];
            }
            return r;
        };

        auto parse_uint_list = [&]
        {
            std::vector<u32> vals;
            vals.push_back(parse_uint());
            while (try_consume(',')) vals.push_back(parse_uint());
            return vals;
        };

        Machine machine;
        consume('[');

        for (u32 shift = 0; i != l && s[i] != ']'; ++shift, ++i)
        {
            bool on = s[i] == '#';
            u32 mask = (u32{on} << shift);
            machine.target_state |= mask;
        }

        consume(']');

        // std::println("{:b}", machine.target);

        consume(' ');

        while (try_consume('('))
        {
            machine.buttons.emplace_back(parse_uint_list());

            consume(')');
            consume(' ');
        }

        consume('{');
        machine.counters = parse_uint_list();
        consume('}');
        assert(i == l);

        return machine;
    }

    inline static constexpr auto as_sview = [](auto l)
    {
        return std::string_view{l};
    };

    template <char pattern>
    inline static constexpr auto split_filter =
        stdv::split(pattern) | stdv::filter(stdr::size) |
        stdv::transform(as_sview);

    static u64 solve(std::string_view input_lines) noexcept
    {
        auto machines = stdr::to<std::vector>(
            input_lines | split_filter<'\n'> | stdv::transform(parse_spec));
        auto joltages = machines | stdv::transform(&Machine::counters);
        std::println("max counter: {}", stdr::max(stdv::join(joltages)));
        std::println(
            "max counters length: {}",
            stdr::max(joltages | stdv::transform(stdr::size)));

        u64 r = 0;
        for (auto& machine : machines)
        {
            logln("");
            logln("-----------------------------------------------");
            logln("    buttons: {}", machine.buttons);
            logln("    counters: {}", machine.counters);
            auto start_time = Clock::now();
            auto presses = RecursiveSolver::min_presses(machine);
            auto finish_time = Clock::now();
            logln("    result: {}", presses);
            logln(
                "    duration: {}",
                std::chrono::duration_cast<std::chrono::seconds>(
                    finish_time - start_time));
            r += presses;
        }

        // auto r = stdr::fold_left(
        //     input_lines | split_filter<'\n'> | stdv::transform(parse_spec) |
        //         stdv::transform(RecursiveSolver::min_presses),
        //     0ul,
        //     std::plus{});

        logln("Result: {}", r);

        return r;
    }
};

}  // namespace part2
