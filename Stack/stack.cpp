#include "dynamic_stack.hpp"
#include <iostream>
#include <vector>

enum ItemType
{
    ADD,
    SUB,
    MUL,
    DIV,
    STRMUL,
    MOD,
    VAL
};

struct Item
{
    ItemType type;
    int value;

    Item(ItemType t, int val = 0)
    {
        type = t;
        value = val;
    }
};

// template <typename T>
// class Stack
// {
// public:
//     Stack(int stackSize = 4)
//     {
//         // stack[stackSize] is where the previous base pointer
//         // would have been stored in an assembly program
//         stack = std::vector<T>(stackSize + 1);

//         // Stack grows from the top
//         rbp = rsp = stackSize;
//     }
//     void push(T val)
//     {
//         if (rbp - rsp - 1 == stack.size() - 1)
//         {
//             std::cerr << "Stack overflow\n";
//             exit(1);
//         }

//         // "alllocate" space, put the value
//         stack[--rsp] = val;
//     }

//     T pop()
//     {
//         // checking if there are elements
//         if (rsp == rbp)
//         {
//             std::cerr << "No elements to pop\n";
//             exit(1);
//         }

//         return stack[rsp++];
//     }

// private:
//     std::vector<T> stack;
//     int rbp;
//     int rsp;
// };

class Calculator
{
public:
    Calculator(std::vector<Item> expr) : stack(4)
    {
        expressions = expr;
        ip = 0;
    }

    int run()
    {
        while (ip < expressions.size())
        {
            stack.print();
            step();
        }

        return stack.pop();
    }

private:
    void step()
    {
        auto next = expressions[ip++];

        if (next.type == VAL)
        {
            stack.push(next.value);
            return;
        }

        int a = stack.pop();
        int b = stack.pop();

        switch (next.type)
        {
        case ADD:
            stack.push(a + b);
            break;
        case SUB:
            stack.push(b - a);
            break;
        case MUL:
            stack.push(a * b);
            break;
        case DIV:
            stack.push(b / a);
            break;
        case STRMUL:
        {
            int c = a * b;
            stack.push(c % 10);

            if (c / 10 > 0)
            {
                stack.push(c / 10);
            }
            break;
        }
        case MOD:
            stack.push(b % a);
        }
    }

    std::vector<Item> expressions;
    int ip;
    DynamicStack stack;
};

int main()
{
    std::vector<Item> expr;

    std::vector<int> digits({0, 3, 0, 8, 1, 8, 1, 6, 7});

    expr.push_back({VAL, 10});

    int cur = 2;
    for (const auto digit : digits)
    {
        expr.push_back({VAL, digit});
        expr.push_back({VAL, cur});
        expr.push_back({STRMUL, 0});
        cur = cur == 2 ? 1 : 2;
    }

    for (int i = 0; i < digits.size(); i++) // summing the digits
    {
        expr.push_back({ADD, 0});
    }

    expr.push_back({VAL, 10});
    expr.push_back({MOD, 0});
    expr.push_back({SUB, 0});

    Calculator calculator(expr);

    std::cout << calculator.run() << "\n";

    return 0;
}
