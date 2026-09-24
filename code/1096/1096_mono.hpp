#include <algorithm>
#include <cassert>
#include <cctype>
#include <memory_resource>
#include <ranges>
#include <string>
#include <vector>

// https://leetcode.com/problems/brace-expansion-ii/

inline static auto pool = std::pmr::unsynchronized_pool_resource{};  // NOLINT

class Solution
{
public:
    using List = std::vector<std::string>;

    static void multiply(List& words, size_t na, size_t nb)
    {
        size_t t = na + nb;
        size_t i = words.size() - t;
        words.resize(words.size() + na * nb);

        for (size_t x = 0; x != t; ++x)
        {
            words[words.size() - (x + 1)] =
                std::move(words[words.size() - (x + 1 + na * nb)]);
        }

        for (size_t ia = words.size() - t, a_end = ia + na; ia != a_end; ++ia)
        {
            for (size_t ib = a_end; ib != words.size(); ++ib)
            {
                words[i++] = words[ia] + words[ib];
            }
        }

        words.resize(i);
    }

    [[nodiscard]] static size_t expand_sub(std::string_view e, List& words)
    {
        size_t i = 0;
        size_t ps = words.size();
        words.push_back("");
        while (i != e.size() && e[i] != ',' && e[i] != '}')
        {
            if (std::isalpha(e[i]))
            {
                char c = e[i++];
                for (auto& s : words | std::views::drop(ps))
                {
                    s.push_back(c);
                }
            }
            else
            {
                assert(e[i] == '{');
                size_t na = words.size() - ps;
                i += expand(e.substr(i), words);
                multiply(words, na, words.size() - (na + ps));
            }
        }

        return i;
    }

    [[nodiscard]] static size_t
    expand_inner(std::string_view e, char stop, List& words)
    {
        size_t ps = words.size();
        size_t i = 0;
        while (e[i] != stop)
        {
            i += e[i] == ',';
            i += expand_sub(e.substr(i), words);
        }
        std::ranges::sort(words | std::views::drop(ps));
        words.erase(
            std::ranges::unique(words | std::views::drop(ps)).begin(),
            words.end());
        return i;
    }

    // returns the number of consumed characted
    [[nodiscard]] static size_t expand(std::string_view e, List& words)
    {
        assert(e.starts_with('{'));
        size_t i = 1;
        i += expand_inner(e.substr(1), '}', words);
        assert(e[i] == '}');
        return i + 1;
    }

    std::vector<std::string> braceExpansionII(
        const std::string& e) const noexcept
    {
        List words;
        [[maybe_unused]] auto t = expand_inner(e, '\0', words);
        assert(t == e.size());
        return words | std::ranges::to<std::vector>();
    }
};
