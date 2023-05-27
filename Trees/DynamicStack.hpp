#include <cstring>
#include <iostream>

template <typename T>
class DynamicStack
{
public:
    DynamicStack(int initialSize = 4)
    {
        // Allocating initial value
        this->initialSize = initialSize;

        stack = new T[initialSize];
        curSize = initialSize;
        cur = 0;
    }

    void push(T value)
    {
        stack[cur++] = value;

        if (cur == curSize)
        {
            // Reallocate
            replaceStack(curSize * 2);
        }
    }

    T pop()
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
        auto *newStack = new T[newSize];

        int copySize = newSize > curSize ? curSize : newSize;

        memcpy(newStack, stack, sizeof(T) * copySize);

        auto *oldStack = stack;

        stack = newStack;
        delete[] oldStack;

        curSize = newSize;
    }

private:
    T *stack = nullptr;
    int cur;
    int curSize;
    int initialSize;
};