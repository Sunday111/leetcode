#pragma once

#include <string>
#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    using u32 = uint32_t;
    [[nodiscard]] static constexpr std::string decodeCiphertext(
        const std::string_view encoded,
        u32 rows)
    {
        const u32 n = static_cast<u32>(encoded.size());
        const u32 columns = n / rows;
        const u32 delta = columns + 1;

        std::string decoded;
        decoded.reserve(n);

        for (u32 i = 0; i != columns; ++i)
        {
            for (u32 j = i; j < n; j += delta)
            {
                decoded.push_back(encoded[j]);
            }
        }

        decoded.resize(decoded.find_last_not_of(' ') + 1);
        return decoded;
    }
};
