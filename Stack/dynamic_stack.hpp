#include <cstring>
#include <iostream>

class DynamicStack
{
public:
    DynamicStack(int initialSize)
    {
        // Allocating initial value
        this->initialSize = initialSize;

        stack = new int[initialSize];
        curSize = initialSize;
        cur = 0;
    }

    void push(int value)
    {
        stack[cur++] = value;

        if (cur == curSize)
        {
            // Reallocate
            replaceStack(curSize * 2);
        }
    }

    int pop()
    {
        auto retValue = stack[--cur];
        // If our element number drops below 1/4 of the stack capacity
        // halve the stack
        // Obviously, we don't do that if the stack hasn't been grown yet
        if (curSize > initialSize && cur < curSize / 4)
        {
            replaceStack(curSize / 2);
        }

        return retValue;
    }

    void print()
    {
        std::cout << "[ ";
        for (int i = 0; i < cur; i++)
        {
            std::cout << stack[i] << " ";
        }
        std::cout << " ]\n";
    }

    ~DynamicStack()
    {
        delete[] stack;
    }

private:
    void replaceStack(int newSize)
    {
        int *newStack = new int[newSize];

        int copySize = newSize > curSize ? curSize : newSize;

        memcpy(newStack, stack, sizeof(int) * copySize);

        int *oldStack = stack;

        stack = newStack;
        delete[] oldStack;

        curSize = newSize;
    }

private:
    int *stack = nullptr;
    int cur;
    int curSize;
    int initialSize;
};