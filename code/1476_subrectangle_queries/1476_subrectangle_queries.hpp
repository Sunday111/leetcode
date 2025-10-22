#include <vector>

class SubrectangleQueries
{
public:
    std::vector<std::vector<int>> data;

    explicit SubrectangleQueries(std::vector<std::vector<int>>& rectangle)
    {
        data = std::move(rectangle);
    }

    void updateSubrectangle(
        size_t row1,
        size_t col1,
        size_t row2,
        size_t col2,
        int newValue)
    {
        for (size_t r = row1; r <= row2; ++r)
        {
            auto it = data[r].begin();
            std::advance(it, col1);
            fill_n(it, col2 - col1 + 1, newValue);
        }
    }

    int getValue(size_t row, size_t col) { return data[row][col]; }
};
