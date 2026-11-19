#include <array>
#include <string_view>

class Spreadsheet
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;

private:
    std::array<std::array<u32, 26>, 1001> rows{};

    [[nodiscard, gnu::always_inline]] inline static constexpr u8 letterIndex(
        char c) noexcept
    {
        return (c - 'A') & 0x7F;
    }

    [[nodiscard, gnu::always_inline]] inline static constexpr u8 charToInt(
        char c) noexcept
    {
        return (c - '0') & 0x7F;
    }

    [[nodiscard, gnu::always_inline]] inline static constexpr u32 parseInt(
        std::string_view str) noexcept
    {
        u32 v = 0;
        for (char c : str)
        {
            v *= 10;
            v += charToInt(c);
        }
        return v;
    }

    [[nodiscard, gnu::always_inline]] inline static constexpr std::pair<u32, u8>
    parseCell(std::string_view cell) noexcept
    {
        u8 column = letterIndex(cell[0]);
        auto row = parseInt(cell.substr(1));
        return {row, column};
    }

    [[nodiscard, gnu::always_inline]] inline u32 cellOrLiteral(
        std::string_view str) const
    {
        if (str.front() < 65) return parseInt(str);
        auto [row, column] = parseCell(str);
        return rows[row][column];
    }

public:
    explicit Spreadsheet(int) noexcept {}

    [[gnu::always_inline]] inline constexpr void setCell(
        std::string_view cell,
        u32 value) noexcept
    {
        auto [row, column] = parseCell(cell);
        rows[row][column] = value;
    }

    constexpr void resetCell(std::string_view cell) noexcept
    {
        setCell(cell, 0);
    }

    [[nodiscard]] constexpr int getValue(std::string_view formula) noexcept
    {
        size_t plus = formula.find('+');
        auto a = cellOrLiteral(formula.substr(1, plus - 1));
        auto b = cellOrLiteral(formula.substr(plus + 1));
        return static_cast<int>(a + b);
    }
};
