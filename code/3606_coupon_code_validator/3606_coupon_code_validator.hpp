#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>
#include <vector>

class Solution
{
public:
    inline static constexpr std::array<std::string_view, 4> kLines{
        "electronics",
        "grocery",
        "pharmacy",
        "restaurant"};
    static std::vector<std::string> validateCoupons(
        std::vector<std::string>& code,
        std::vector<std::string>& businessLine,
        std::vector<bool>& isActive) noexcept
    {
        auto is_valid_char = [](char c)
        {
            return isalnum(c) || c == '_';
        };
        auto is_valid_code = [&](size_t i)
        {
            return code[i].size() &&
                   std::ranges::all_of(code[i], is_valid_char);
        };
        auto is_valid_line = [&](std::string_view l)
        {
            return std::ranges::contains(kLines, l);
        };
        auto is_valid = [&](size_t i)
        {
            return isActive[i] && is_valid_line(businessLine[i]) &&
                   is_valid_code(i);
        };
        auto indices = std::ranges::to<std::vector>(
            std::views::iota(0uz, code.size()) | std::views::filter(is_valid));

        auto order = [&](size_t i) -> std::tuple<char, std::string_view>
        {
            return {businessLine[i][0], code[i]};
        };

        std::ranges::sort(indices, std::less{}, order);

        auto& r = businessLine;
        r.clear();
        r.reserve(indices.size());
        for (size_t i : indices) r.emplace_back(std::move(code[i]));

        return std::move(r);
    }
};
