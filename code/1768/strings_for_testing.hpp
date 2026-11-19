#pragma once

#include "random_strings.hpp"

struct StringsForTesting
{
    [[nodiscard]] static const StringsForTesting& Get() noexcept
    {
        static auto instance = []()
        {
            StringsForTesting r;
            RandomStringsParams params{
                .string_params{
                    .char_distribution{},
                    .length = std::uniform_int_distribution{10u, 1000u},
                },
                .num_distribution = 500u,
            };
            constexpr unsigned kSeed = 12345;
            std::mt19937 rnd{kSeed};
            r.strings = make_random_strings(rnd, params);
            return r;
        }();
        return instance;
    }

    std::vector<std::string> strings;
};
