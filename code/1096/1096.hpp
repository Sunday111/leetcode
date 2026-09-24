// https://leetcode.com/problems/brace-expansion-ii/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <memory_resource>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

inline static auto pool = std::pmr::unsynchronized_pool_resource{};  // NOLINT

class Solution
{
public:
    using Set = std::pmr::unordered_set<std::string>;
    using List = std::pmr::vector<std::string>;

    [[nodiscard]] static size_t expand_sub(std::string_view e, Set& out)
    {
        Set tmp;
        size_t i = 0;
        List local(&pool);
        local.push_back("");
        while (i != e.size() && e[i] != ',' && e[i] != '}')
        {
            if (std::isalpha(e[i]))
            {
                char c = e[i++];
                for (auto& s : local)
                {
                    s.push_back(c);
                }
            }
            else
            {
                assert(e[i] == '{');
                tmp.clear();
                i += expand(e.substr(i), tmp);
                size_t k = local.size();
                local.reserve(k * tmp.size());
                for (size_t li = 0; li != k; ++li)
                {
                    auto it = tmp.begin();
                    for (size_t ti = 1; ti < tmp.size(); ++ti, ++it)
                    {
                        local.push_back(local[li] + *it);
                    }
                    local[li] += *it;
                }
            }
        }

        for (auto& word : local)
        {
            out.emplace(std::move(word));
        }

        return i;
    }

    [[nodiscard]] static size_t
    expand_inner(std::string_view e, char stop, Set& out)
    {
        size_t i = 0;
        while (e[i] != stop)
        {
            i += e[i] == ',';
            i += expand_sub(e.substr(i), out);
        }
        return i;
    }

    // returns the number of consumed characted
    [[nodiscard]] static size_t expand(std::string_view e, Set& out)
    {
        assert(e.starts_with('{'));
        size_t i = 1;
        i += expand_inner(e.substr(1), '}', out);
        assert(e[i] == '}');
        return i + 1;
    }

    std::vector<std::string> braceExpansionII(
        const std::string& e) const noexcept
    {
        Set s;
        [[maybe_unused]] auto t = expand_inner(e, '\0', s);
        assert(t == e.size());
        auto r = s | std::ranges::to<std::vector>();
        std::ranges::sort(r);
        return r;
    }
};
