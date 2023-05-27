#if !defined(HEAP_HPP)
#define HEAP_HPP

#include <optional>
#include <vector>

class Heap
{
public:
    Heap(int initialCapacity)
    {
        heap = std::vector<int>(initialCapacity);
        size = 0;
    }

    void add(int value)
    {
        checkCapacity();
        // k + 1
        heap[size] = value;
        size++;
        bubbleUp();
    }

    void push(int increment)
    {
        if (size == 0)
            return;

        heap[0] += increment;
        sink();
    }

    std::optional<int> remove()
    {
        if (empty())
        {
            return std::nullopt;
        }

        auto value = std::optional<int>(heap[0]);
        heap[0] = heap[size - 1];
        size--;

        sink();

        return value;
    }

    bool empty()
    {
        return size == 0;
    }

private:
    // work on both even and odd numbers due to rounding down
    inline int getParentIndex(int childInd) { return (childInd - 1) / 2; }
    inline bool hasParent(int childInd) { return getParentIndex(childInd) >= 0; }
    inline int getLeftChildInd(int parentInd) { return 2 * parentInd + 1; }
    inline int hasLeftChild(int parentInd) { return getLeftChildInd(parentInd) < size; }
    inline int getRightChildInd(int parentInd) { return 2 * parentInd + 2; }
    inline int hasRightChild(int parentInd) { return getRightChildInd(parentInd) < size; }
    inline int getSmallestInd(int parentInd)
    {
        int leftChildInd = getLeftChildInd(parentInd);
        int curMin = parentInd;
        if (heap[parentInd] > heap[leftChildInd])
            curMin = leftChildInd;
        if (hasRightChild(parentInd))
        {
            int rightChildInd = getRightChildInd(parentInd);
            if (heap[curMin] > heap[rightChildInd])
                curMin = rightChildInd;
        }
        return curMin;
    }

    inline void sink()
    {
        int curInd = 0; // root node

        while (hasLeftChild(curInd))
        {
            int smallestInd = getSmallestInd(curInd);
            if (smallestInd == curInd)
                return;

            std::swap(heap[curInd], heap[smallestInd]);
            curInd = smallestInd;
        }
    }

    inline void bubbleUp()
    {
        // now we have to bubble it up
        int curInd = size - 1;
        while (hasParent(curInd) && heap[curInd] < heap[getParentIndex(curInd)])
        {
            std::swap(heap[curInd], heap[getParentIndex(curInd)]);
            curInd = getParentIndex(curInd);
        }
    }

    void checkCapacity()
    {
        if (size == heap.size())
        {
            heap.resize(heap.size() * 2);
        }
    }

    int size;
    std::vector<int> heap;
};

#endif // HEAP_HPP
