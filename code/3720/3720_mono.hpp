#include <optional>
#include <string>


#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    void complete(char* s, const size_t* f)
    {
        for (size_t i = 0; i != 26; ++i)
        {
            for (size_t j = 0; j != f[i]; ++j)
            {
                *(s++) = static_cast<char>(i + 'a');
            }
        }
    }

    std::string lexGreaterPermutation(std::string& s, std::string& target)
    {
        size_t fs[26]{};
        for (char c : s) fs[c - 'a']++;

        std::optional<std::string> r;

        for (size_t i = 0; i != s.size(); ++i)
        {
            int c = target[i] - 'a' + 1;
            while (c != 26 && !fs[c]) ++c;
            if (c != 26)
            {
                --fs[c];
                s[i] = static_cast<char>(c + 'a');
                complete(s.data() + i + 1, fs);
                if (!r || s < r.value())
                {
                    r = s;
                }
                ++fs[c];
            }

            c = static_cast<int>(target[i]);  // NOLINT
            if (!fs[c - 'a']) break;
            s[i] = static_cast<char>(c);
            --fs[c - 'a'];
        }

        return std::move(r).value_or("");
    }
};
