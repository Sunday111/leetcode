#pragma once

#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u8 countStudents(
        std::vector<int>& students,
        const std::vector<int>& sandwiches) noexcept
    {
        u8 num_prefer_circle = 0, num_prefer_square = 0;
        for (auto sandwich_type : students)
        {
            ++*(sandwich_type ? &num_prefer_square : &num_prefer_circle);
        }

        u8 next_sandwich = 0, next_student = 0;
        while (true)
        {
            if (const auto sandwich = sandwiches[next_sandwich];
                sandwich == students[next_student])
            {
                // leave the queue
                students.erase(std::next(students.begin(), next_student));
                --*(sandwich ? &num_prefer_square : &num_prefer_circle);
                if (++next_sandwich == sandwiches.size()) return 0;
                if (next_student == students.size()) next_student = 0;
            }
            else
            {
                if (!(sandwich ? num_prefer_square : num_prefer_circle))
                {
                    return num_prefer_circle + num_prefer_square;
                }

                if (++next_student == students.size()) next_student = 0;
            }
        }

        std::unreachable();
    }
};
