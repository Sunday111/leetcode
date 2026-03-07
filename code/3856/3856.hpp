#include <string>
#include <string_view>

class Solution
{
public:
    inline static constexpr auto kVowels = []
    {
        int x = 0;
        for (char c : std::string_view("aeiou"))
        {
            x |= (1 << (c - 'a'));
        }
        return x;
    }();

    std::string trimTrailingVowels(std::string& s)
    {
        while (s.size() && (kVowels & (1 << (s.back() - 'a'))))
        {
            s.pop_back();
        }
        return std::move(s);
    }
};
