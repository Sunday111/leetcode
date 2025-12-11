#include "aoc_2025_10.hpp"

namespace part1
{

struct Machine
{
    u32 target_state = 0;

    std::vector<std::vector<u32>> buttons;
    std::vector<u32> masks;
    std::vector<u32> exclusivity;

    std::vector<u32> joltages;
};

namespace stdr = std::ranges;
namespace stdv = std::views;

class Solution
{
public:
    static Machine parse_line(std::string_view s)
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
        machine.joltages = parse_uint_list();
        consume('}');
        assert(i == l);

        stdr::sort(machine.buttons, std::greater{}, stdr::size);

        for (auto& btn : machine.buttons)
        {
            u32& mask = machine.masks.emplace_back(0u);
            for (u32 bit : btn)
            {
                assert(!(mask & (1u << bit)));
                mask |= (1u << bit);
            }
        }

        for (u32 a = 0; a != machine.buttons.size(); ++a)
        {
            u32& excl = machine.exclusivity.emplace_back(machine.masks[a]);
            for (u32 b = 0; b != machine.buttons.size(); ++b)
            {
                if (a != b) excl &= ~machine.masks[b];
            }
        }

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

    static u32 final_state(const Machine& machine, u32 pressed)
    {
        u32 state = 0;

        while (pressed)
        {
            u32 button_index = cast<u32>(std::countr_zero(pressed));
            state ^= machine.masks[button_index];
            pressed &= ~(1u << button_index);
        }

        return state;
    }

    static u64 min_presses(const Machine& machine)
    {
        logln("");
        logln("Case");
        logln("    buttons: {}", machine.buttons);
        log("    masks: ");
        for (u32 mask : machine.masks) log("{:b} ", mask);
        logln("");
        logln("    target: {:b}", machine.target_state);

        u32 r = cast<u32>(machine.buttons.size());
        u32 lim_pressed = 1u << machine.buttons.size();
        for (u32 pressed = 0; pressed < lim_pressed; ++pressed)
        {
            u32 state = final_state(machine, pressed);
            u32 num_pressed = cast<u32>(std::popcount(pressed));
            logln("        {:10b} -> {}", pressed, num_pressed);
            if (state == machine.target_state)
            {
                if (num_pressed < r)
                {
                    r = num_pressed;
                }
            }
        }

        logln("    requires {} presses", r);

        return r;
    }

    static u64 solve(std::string_view input_lines) noexcept
    {
        auto r = stdr::fold_left(
            input_lines | split_filter<'\n'> | stdv::transform(parse_line) |
                stdv::transform(min_presses),
            0ul,
            std::plus{});

        logln("Result: {}", r);

        return r;
    }
};
}  // namespace part1
