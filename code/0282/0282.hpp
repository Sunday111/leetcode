#pragma once

#include <format>
#include <string>
#include <vector>

class Solution
{
public:
    std::string_view input;
    std::vector<std::string> variants;
    int64_t target = 0;
    int64_t subtotal = 0;
    int64_t mult = 0;
    std::vector<int64_t> operands;
    std::vector<char> operators;

    void addVariant()
    {
        std::string s;
        s.reserve(input.size() + operators.size() - 1);

        for (size_t i = 1; i != operands.size() - 1; ++i)
        {
            std::format_to(std::back_inserter(s), "{}", operands[i]);
            s.push_back(operators[i]);
        }

        std::format_to(std::back_inserter(s), "{}", operands.back());

        variants.emplace_back(std::move(s));
    }

    void addOperand(std::string_view s)
    {
        if (s.empty()) return;

        size_t i = 0;
        auto& operand = operands.emplace_back(0);
        while (i != s.size())
        {
            operand = (operand * 10) + (s[i] - '0');

            auto psub = subtotal;
            auto pm = mult;

            switch (operators.back())
            {
            case '*':
                subtotal += mult * operand - mult;
                mult *= operand;
                break;

            case '+':
                subtotal += operand;
                break;

            case '-':
                subtotal -= operand;
                break;
            }

            if (++i == s.size())
            {
                if (subtotal == target)
                {
                    addVariant();
                }
            }
            else
            {
                addOperator(s.substr(i));
            }

            subtotal = psub;
            mult = pm;

            if (i == 1 && operand == 0) break;
        }

        operands.pop_back();
    }

    void addOperator(std::string_view s)
    {
        if (s.empty()) return;

        // + and -
        {
            operators.push_back('+');
            addOperand(s);
            operators.back() = '-';
            addOperand(s);
            operators.pop_back();
        }

        // multiplication
        {
            switch (operators.back())
            {
            case '+':
                mult = operands.back();
                break;
            case '-':
                mult = -operands.back();
                break;
            case '*':
                break;
            }

            operators.push_back('*');
            addOperand(s);
            operators.pop_back();
        }
    }

    std::vector<std::string> addOperators(std::string_view num, int in_target)
    {
        input = num;

        variants.clear();

        operators.clear();
        operators.reserve(20);
        operators.push_back('+');

        operands.clear();
        operands.reserve(20);
        operands.push_back(0);

        target = in_target;
        mult = 0;
        subtotal = 0;

        addOperand(num);
        return variants;
    }
};
