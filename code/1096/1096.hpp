// https://leetcode.com/problems/brace-expansion-ii/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <ranges>
#include <string>
#include <vector>

#include "namespaces.hpp"
#include "sync_stdio.hpp"

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
        const size_t ps = words.size();
        size_t i = 0;
        words.push_back("");
        while (i != e.size() && e[i] != ',' && e[i] != '}')
        {
            if (std::isalpha(e[i]))
            {
                char c = e[i++];
                for (auto& s : words | stdv::drop(ps))
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
        const size_t ps = words.size();
        size_t i = 0;
        while (e[i] != stop)
        {
            i += e[i] == ',';
            i += expand_sub(e.substr(i), words);
        }
        stdr::sort(words | stdv::drop(ps));
        words.erase(stdr::unique(words | stdv::drop(ps)).begin(), words.end());
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
        return words;
    }
};
