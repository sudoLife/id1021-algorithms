#if !defined(DYNAMIC_QUEUE_HPP)
#define DYNAMIC_QUEUE_HPP

#include <cstring>
#include <iostream>

// Queue implementation using dynamic arrays
template <typename ValueType>
class DynamicQueue
{
public:
    DynamicQueue(int size) : curSize(size)
    {
        queue = new ValueType[curSize];
        end = start = 0;
        elems = 0;
    }

    void push(const ValueType val) noexcept
    {
        queue[end++] = val;
        elems++;

        checkHealth();
    }

    ValueType pop()
    {
        // UPD: added this check
        if (empty())
            throw std::runtime_error("Cannot pop from an empty queue");
        auto retValue = queue[start++];
        elems--;

        checkHealth();

        return retValue;
    }

    bool empty() const
    {
        return (elems == 0);
    }

    ~DynamicQueue()
    {
        delete[] queue;
    }
    void print()
    {
        if (end < start)
        {
            for (int i = start; i < curSize; i++)
            {
                std::cout << queue[i] << ' ';
            }

            for (int i = 0; i < end; i++)
            {
                std::cout << queue[i] << ' ';
            }
        }
        else
        {
            for (int i = start; i < end; i++)
            {
                std::cout << queue[i] << ' ';
            }
        }

        std::cout << '\n';
    }

private:
    inline void checkHealth()
    {
        checkWrap();
        checkResize();
    }

    inline void checkWrap()
    {
        // UPD: wrapping the head
        if (start == curSize)
        {
            start = 0;
        }

        // already wrapped
        if (end <= start)
            return;

        if (end == curSize && start > 0)
        {
            end = 0;
        }
    }

    inline void checkResize()
    {
        auto beginningSize = curSize - start;
        ValueType *newQueue = nullptr;
        int newSize = 0;
        // double
        if (elems == curSize)
        {
            newSize = curSize * 2;

            newQueue = new ValueType[newSize];

            // copy the first half
            std::memcpy(newQueue, queue + start, sizeof(ValueType) * beginningSize);
            // check if wrapped
            if (end == start)
            {
                // at this point we're certain we're not at 0 elements
                std::memcpy(newQueue + beginningSize, queue, sizeof(ValueType) * end);
            }
        }

        // halve
        // adding 'else' for readability, they'll never fire together
        else if (elems < curSize / 4)
        {
            newSize = curSize / 2;
            newQueue = new ValueType[newSize];

            // not wrapped
            if (end > start)
            {
                std::memcpy(newQueue, queue + start, sizeof(ValueType) * elems);
            }
            else
            {
                std::memcpy(newQueue, queue + start, sizeof(ValueType) * beginningSize);
                std::memcpy(newQueue + beginningSize, queue, sizeof(ValueType) * end);
            }
        }

        if (newQueue == nullptr) // don't update
            return;

        curSize = newSize;
        start = 0;
        end = start + elems;

        delete[] queue;
        queue = newQueue;

        return;
    }

private:
    ValueType *queue = nullptr;

    int curSize;
    int start; // points to the first element
    int end;   // points to the vacant space
    int elems; // number of elements
};

#endif // DYNAMIC_QUEUE_HPP
