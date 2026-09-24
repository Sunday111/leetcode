// https://leetcode.com/problems/brace-expansion-ii/

#include <cassert>
#include <cctype>
#include <memory_resource>
#include <set>
#include <string>
#include <vector>

#include "sync_stdio.hpp"

inline static std::pmr::unsynchronized_pool_resource pool;  // NOLINT

class Solution
{
public:
    using Set = std::pmr::set<std::string>;

    static void multiply(Set& words, const Set& rhs)
    {
        Set result(&pool);
        while (!words.empty() && !rhs.empty())
        {
            auto node = words.extract(words.begin());
            size_t prefix_size = node.value().size();
            auto it = rhs.begin();
            while (true)
            {
                node.value() += *it;
                if (++it == rhs.end())
                {
                    result.insert(std::move(node));
                    break;
                }
                result.emplace(node.value());
                node.value().resize(prefix_size);
            }
        }

        words.swap(result);
    }

    [[nodiscard]] static size_t expand_sub(std::string_view e, Set& words)
    {
        Set local(&pool);
        size_t i = 0;
        local.emplace("");
        while (i != e.size() && e[i] != ',' && e[i] != '}')
        {
            if (std::isalpha(e[i]))
            {
                size_t j = i;
                while (std::isalpha(e[j])) ++j;

                auto word = e.substr(i, j - i);
                i = j;

                Set tmp = std::move(local);
                while (!tmp.empty())
                {
                    auto node = tmp.extract(tmp.begin());
                    node.value() += word;
                    local.insert(std::move(node));
                }
            }
            else
            {
                assert(e[i] == '{');
                Set tmp(&pool);
                i += expand(e.substr(i), tmp);
                multiply(local, tmp);
            }
        }

        words.merge(std::move(local));

        return i;
    }

    [[nodiscard]] static size_t
    expand_inner(std::string_view e, char stop, Set& words)
    {
        size_t i = 0;
        while (e[i] != stop)
        {
            i += e[i] == ',';
            i += expand_sub(e.substr(i), words);
        }
        return i;
    }

    // returns the number of consumed characted
    [[nodiscard]] static size_t expand(std::string_view e, Set& words)
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
        Set words(&pool);
        [[maybe_unused]] auto t = expand_inner(e, '\0', words);
        assert(t == e.size());
        std::vector<std::string> result;

        result.reserve(words.size());
        while (!words.empty())
        {
            auto node = words.extract(words.begin());
            result.push_back(std::move(node.value()));
        }
        return result;
    }
};
