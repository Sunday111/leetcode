#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    static constexpr auto kMaxU16 = std::numeric_limits<u16>::max();
    [[nodiscard]] static constexpr std::string answerString(
        std::string_view word,
        u16 k) noexcept
    {
        const auto n = static_cast<u16>(word.size());
        if (k == 1) return std::string{word};

        std::vector<u16> biggest_chars(word.size());
        u16 num_biggest_chars = 0;
        char biggest_char = word.front();
        biggest_chars[num_biggest_chars++] = 0;

        for (u16 i = 1; i != n; ++i)
        {
            char c = word[i];
            if (c < biggest_char) continue;
            if (c > biggest_char)
            {
                biggest_char = c;
                num_biggest_chars = 0;
            }
            biggest_chars[num_biggest_chars++] = i;
        }

        const u16 max_segment_size = (n + 1) - k;
        std::string_view r = "";
        for (u16 i = 0; i != num_biggest_chars; ++i)
        {
            auto segment = word.substr(biggest_chars[i]);
            segment = segment.substr(
                0,
                std::min<size_t>(segment.size(), max_segment_size));
            if (segment > r) r = segment;
        }

        return std::string(r);
    }
};
