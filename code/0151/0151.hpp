#include <algorithm>
#include <ranges>
#include <string>

class Solution
{
public:
    std::string reverseWords(std::string& s) noexcept
    {
        std::ranges::reverse(s);
        char* o = s.data();
        for (auto word :
             s | std::views::split(' ') | std::views::filter(std::ranges::size))
        {
            auto po = o;
            o = std::ranges::copy(word, o).out;
            std::reverse(po, o);
            *(o++) = ' ';
        }
        o -= o != s.data();
        s.resize(static_cast<size_t>(o - s.data()));
        return std::move(s);
    }
};
