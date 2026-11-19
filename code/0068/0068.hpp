#pragma once

#include <algorithm>
#include <cassert>
#include <span>
#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::string> fullJustify(
        const std::vector<std::string>& all_words,
        size_t line_width) noexcept
    {
        std::span words{all_words};

        std::vector<std::string> lines;
        lines.reserve(words.size());

        while (!words.empty())
        {
            std::string& line = lines.emplace_back();
            line.resize(line_width, ' ');

            // First word
            auto it = line.begin();
            std::ranges::copy(words.front(), it);
            std::advance(it, words.front().size());

            size_t num_line_words = 1;
            size_t min_required_length = words.front().size();
            bool last_line = false;
            while (true)
            {
                if (num_line_words == words.size())
                {
                    last_line = true;
                    break;
                }

                size_t new_req_len =
                    words[num_line_words].size() + 1 + min_required_length;
                if (new_req_len > line_width) break;

                ++num_line_words;
                min_required_length = new_req_len;
            }

            if (num_line_words > 1)
            {
                if (last_line)
                {
                    for (const auto& word : words.subspan(1))
                    {
                        std::advance(it, 1);
                        std::ranges::copy(word, it);
                        std::advance(it, word.size());
                    }
                }
                else
                {
                    size_t num_holes = num_line_words - 1;
                    size_t total_spaces =
                        line_width - (min_required_length - num_holes);
                    size_t const_spaces = total_spaces / num_holes;
                    size_t rem_spaces = total_spaces % num_holes;

                    for (const auto& word :
                         words.subspan(0, num_line_words).subspan(1))
                    {
                        size_t ns = const_spaces;
                        if (rem_spaces != 0)
                        {
                            ++ns;
                            --rem_spaces;
                        }
                        std::advance(it, ns);
                        std::ranges::copy(word, it);
                        std::advance(it, word.size());
                    }
                }
            }

            words = words.subspan(num_line_words);
        }

        return lines;
    }
};
