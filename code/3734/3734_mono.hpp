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
    void complete(char* front, char* back, const size_t* f)
    {
        for (size_t i = 0; i != 26; ++i)
        {
            for (size_t j = 0; j != f[i]; ++j)
            {
                *(front++) = static_cast<char>(i + 'a');
                *(back--) = static_cast<char>(i + 'a');
            }
        }
    }

    std::string lexPalindromicPermutation(std::string& s, std::string& target)
    {
        const size_t n = s.size(), n2 = n / 2;
        size_t fs[26]{}, i = 0, j = n - 1;

        for (char c : s)
        {
            fs[c - 'a']++;
        }

        for (size_t g = 0, c = 0; c != 26; ++c)
        {
            if (fs[c] & 1)
            {
                if (g++)
                {
                    return "";
                }
                s[n2] = static_cast<char>(c + 'a');
            }
            fs[c] /= 2;
        }

        std::optional<std::string> r;

        while (i < j)
        {
            int c = target[i] - 'a' + 1;
            while (c != 26 && !fs[c]) ++c;
            if (c != 26)
            {
                --fs[c];
                s[i] = s[j] = static_cast<char>(c + 'a');
                complete(s.data() + i + 1, s.data() + j - 1, fs);
                if (!r || s < r.value()) r = s;
                ++fs[c];
            }

            c = static_cast<int>(target[i]);  // NOLINT
            if (!fs[c - 'a']) break;
            s[i++] = s[j--] = static_cast<char>(c);
            --fs[c - 'a'];
        }

        if (i >= j && s > target && (!r || s < r.value())) r = s;

        return std::move(r).value_or("");
    }
};
