#pragma once

#include <array>
#include <random>
#include <variant>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "overload.hpp"

template <std::integral T, typename Rnd>
[[nodiscard]] inline auto get_val(
    Rnd& rnd,
    std::variant<T, std::uniform_int_distribution<T>>& src) noexcept
{
    return std::visit(
        Overload{
            [&](std::uniform_int_distribution<T>& distr) { return distr(rnd); },
            [](T v) { return v; }},
        src);
}

struct RandomStringParams
{
    // What characters
    std::uniform_int_distribution<u32> char_distribution{'a', 'z'};

    // How many characters
    std::variant<u32, std::uniform_int_distribution<u32>> length;
};

[[nodiscard]] constexpr std::string make_random_string(
    auto& rnd,
    RandomStringParams& params) noexcept
{
    const u32 l = get_val(rnd, params.length);

    std::string r;
    r.reserve(l);

    std::array<char, 1024> buffer;  // NOLINT

    const u32 full_buffers = l / buffer.size();
    for (u32 i = 0; i != full_buffers; ++i)
    {
        for (u32 j = 0; j != buffer.size(); ++j)
        {
            buffer[j] = cast<char>(params.char_distribution(rnd));
        }

        r.append(buffer.begin(), buffer.end());
    }

    const u32 remainder = l % buffer.size();
    for (u32 j = 0; j != remainder; ++j)
    {
        buffer[j] = cast<char>(params.char_distribution(rnd));
    }

    r.append(buffer.begin(), std::next(buffer.begin(), remainder));

    return r;
}

struct RandomStringsParams
{
    // What string
    RandomStringParams string_params;

    // How many strings
    std::variant<u32, std::uniform_int_distribution<u32>> num_distribution;
};

[[nodiscard]] constexpr std::vector<std::string> make_random_strings(
    auto& rnd,
    RandomStringsParams& params) noexcept
{
    u32 num_strings = get_val(rnd, params.num_distribution);
    std::vector<std::string> r;
    r.reserve(num_strings);

    for (u32 i = 0; i != num_strings; ++i)
    {
        r.emplace_back(make_random_string(rnd, params.string_params));
    }

    return r;
}
