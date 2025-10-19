#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <unordered_set>

#define FORCE_INLINE inline __attribute__((always_inline))

using u8 = uint8_t;
using u64 = uint64_t;

struct SmallString
{
    std::array<char, 101> data{};
    uint8_t len = 0;

    [[nodiscard]] FORCE_INLINE std::string_view view() const noexcept
    {
        return std::string_view{data.begin(), len};
    }

    [[nodiscard]] FORCE_INLINE constexpr bool operator<(
        const SmallString& s) const noexcept
    {
        return view() < s.view();
    }

    [[nodiscard]] FORCE_INLINE constexpr bool operator==(
        const SmallString& s) const noexcept
    {
        return view() == s.view();
    }

    struct Hasher
    {
        [[nodiscard]] FORCE_INLINE size_t
        operator()(const SmallString& s) const noexcept
        {
            return std::hash<std::string_view>{}(s.view());
        }
    };
};

class Solution
{
public:
    [[nodiscard]] static SmallString toSmallString(
        const std::string& s) noexcept
    {
        SmallString r;
        std::ranges::copy(s, r.data.begin());
        r.len = s.size() & 0xFF;
        return r;
    }

    std::unordered_set<SmallString, SmallString::Hasher> visited;
    SmallString r;
    u8 a = 0, b = 0, n = 0;

    void dfs(const SmallString& s)
    {
        if (visited.contains(s)) return;
        visited.insert(s);
        if (s < r) r = s;

        auto copy = s;
        for (u8 i = 1; i < n; i += 2)
        {
            char& c = copy.data[i];
            c = static_cast<char>(((c + a - '0') % 10) + '0');
        }

        dfs(copy);
        copy = s;

        std::rotate(
            copy.data.begin(),
            copy.data.begin() + copy.len - b,
            copy.data.begin() + copy.len);
        dfs(copy);
    }

    [[nodiscard]] std::string
    findLexSmallestString(std::string& s, u8 a_, u8 b_) noexcept
    {
        auto input = toSmallString(s);
        r = input, a = a_, b = b_, n = s.size() & 0xFF;
        dfs(input);

        return std::string{r.view()};
    }
};
