#if !defined(HEAP_HPP)
#define HEAP_HPP

#include "Entry.hpp"
#include <optional>
#include <vector>

class Heap
{
public:
    Heap(int maxCities)
    {
        heap = std::vector<Entry>(maxCities);

        // in the beginning, none of them are in the queue.
        positions = std::vector<int>(maxCities, -1);

        size = 0;
    }

    void add(Entry entry)
    {
        checkCapacity();
        // k + 1
        heap[size] = entry;
        positions[entry.city->id] = size;
        size++;
        bubbleUp();
    }

    inline Entry &peek(int ind)
    {
        return heap[ind];
    }

    bool exists(int id)
    {
        return (positions[id] != -1);
    }

    Entry remove()
    {
        if (empty())
        {
            throw std::runtime_error("remove on an empty queue");
        }

        Entry retvalue = heap[0];
        positions[retvalue.city->id] = -1;
        heap[0] = heap[size - 1];
        size--;

        sink();

        return retvalue;
    }

    bool empty()
    {
        return size == 0;
    }

    // we need a method to change the priority of an element upwards
    // so suppose we found a shorter path to an element.
    // We check if it's enqued
    // and if it is, we modify its entry and then bubble it up by index
    inline void bubbleUp(int curInd = -1)
    {
        // now we have to bubble it up
        if (curInd == -1)
            curInd = size - 1;
        while (hasParent(curInd) && heap[curInd].traversed < heap[getParentIndex(curInd)].traversed)
        {
            swap(heap[curInd], heap[getParentIndex(curInd)]);
            curInd = getParentIndex(curInd);
        }
    }

public:
    std::vector<int> positions;

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
        if (heap[parentInd].traversed > heap[leftChildInd].traversed)
            curMin = leftChildInd;
        if (hasRightChild(parentInd))
        {
            int rightChildInd = getRightChildInd(parentInd);
            if (heap[curMin].traversed > heap[rightChildInd].traversed)
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

            swap(heap[curInd], heap[smallestInd]);
            curInd = smallestInd;
        }
    }

    void checkCapacity()
    {
        if (size == heap.size())
        {
            heap.resize(heap.size() * 2);
        }
    }

    void swap(Entry &first, Entry &second)
    {
        std::swap(first, second);
        std::swap(positions[first.city->id], positions[second.city->id]);
    }

    int size;
    std::vector<Entry> heap;
};

#endif // HEAP_HPP
