#include <cstring>
#include <iostream>

class StaticStack
{
public:
    StaticStack(int initialSize)
    {
        stack = new int[initialSize];
        size = initialSize;
        cur = 0;
    }

    void push(int value)
    {
        stack[cur++] = value;
    }

    int pop()
    {
        auto retValue = stack[--cur];
        return retValue;
    }

    ~StaticStack()
    {
        delete[] stack;
    }

private:
    int *stack = nullptr;
    int cur;
    int size;
};