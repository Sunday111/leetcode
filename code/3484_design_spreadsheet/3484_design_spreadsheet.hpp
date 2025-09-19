#include <array>
#include <string_view>

#define FORCE_INLINE inline __attribute__((always_inline))
class Spreadsheet
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

private:
    std::array<std::array<u32, 26>, 1001> rows{};

    [[nodiscard]] FORCE_INLINE static constexpr u8 letterIndex(char c) noexcept
    {
        return (c - 'A') & 0x7F;
    }

    [[nodiscard]] FORCE_INLINE static constexpr u8 charToInt(char c) noexcept
    {
        return (c - '0') & 0x7F;
    }

    [[nodiscard]] FORCE_INLINE static constexpr u32 parseInt(
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

    [[nodiscard]] FORCE_INLINE static constexpr std::pair<u32, u8> parseCell(
        std::string_view cell) noexcept
    {
        u8 column = letterIndex(cell[0]);
        auto row = parseInt(cell.substr(1));
        return {row, column};
    }

    [[nodiscard]] FORCE_INLINE u32 cellOrLiteral(std::string_view str) const
    {
        if (str.front() < 65) return parseInt(str);
        auto [row, column] = parseCell(str);
        return rows[row][column];
    }

public:
    explicit Spreadsheet(int) noexcept {}

    FORCE_INLINE constexpr void setCell(
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
