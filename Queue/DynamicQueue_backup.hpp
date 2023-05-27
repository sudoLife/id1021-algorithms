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
    }

    void push(const ValueType val)
    {
        queue[end++] = val;

        // time to check if we are at our limit
        if (end == curSize)
        {
            // try to wrap it around
            end = 0; // might give me troubles
        }

        if (end == start) // Unfortunately we're fully booked
        {
            doubleSize();
        }
    }

    bool empty()
    {
        return (start == end && start == 0); // TODO: make sure this holds with all the wraparound going on
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

    ValueType pop()
    {
    }

    ~DynamicQueue()
    {
        delete[] queue;
    }

private:
    void doubleSize()
    {
        int newSize = curSize * 2;
        std::cout << "Resizing from " << curSize << " to " << newSize << '\n';

        auto *newQueue = new ValueType[newSize];

        int beginningSize = curSize - start;
        std::memcpy(newQueue, queue + start, sizeof(ValueType) * beginningSize);
        // going to fail when we're circling
        std::memcpy(newQueue + beginningSize, queue, sizeof(ValueType) * end);

        delete[] queue;
        queue = newQueue;

        start = 0;
        end = curSize; // k = n + 1
        curSize = newSize;
    }

    inline void incrementEnd()
    {
        int perhaps_its = end + 1;

        if (perhaps_its == curSize && start == 0)
        {
            // doubleSize();
            // SIMPLE copy and doubling
        }
    }

private:
    ValueType *queue = nullptr;

    int curSize;
    int start;
    int end; // points to the vacant space
};

#endif // DYNAMIC_QUEUE_HPP
