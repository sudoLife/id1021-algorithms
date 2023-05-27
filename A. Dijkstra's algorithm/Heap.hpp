#if !defined(HEAP_HPP)
#define HEAP_HPP

#include "City.hpp"
#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

class Heap
{
public:
    Heap(int maxCities)
    {
        heap = std::vector<City *>(maxCities);

        // in the beginning, none of them are in the queue.
        positions = std::vector<int>(maxCities, -1);

        size = 0;
    }

    void addOrBubble(City *city)
    {
        if (exists(city->id))
        {
            bubbleUp(positions[city->id]);
        }
        else
        {
            add(city);
        }
    }

    void add(City *city)
    {
        checkCapacity();
        // k + 1
        heap[size] = city;
        positions[city->id] = size;
        size++;
        bubbleUp();
    }

    inline City *peek(int ind)
    {
        return heap[ind];
    }

    bool exists(int id)
    {
        return (positions[id] != -1);
    }

    City *remove()
    {
        if (empty())
        {
            throw std::runtime_error("remove on an empty queue");
        }
        City *retvalue = heap[0];
        assert(positions[retvalue->id] == 0);

        positions[retvalue->id] = -1;

        if (size == 1)
        {
            heap[0] = nullptr;
        }
        else
        {
            heap[0] = heap[size - 1];
            positions[heap[0]->id] = 0;
        }
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
        while (hasParent(curInd) && heap[curInd]->traversed < heap[getParentIndex(curInd)]->traversed)
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
        if (heap[parentInd]->traversed > heap[leftChildInd]->traversed)
            curMin = leftChildInd;
        if (hasRightChild(parentInd))
        {
            int rightChildInd = getRightChildInd(parentInd);
            if (heap[curMin]->traversed > heap[rightChildInd]->traversed)
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

    void swap(City *first, City *second)
    {
        assert(positions[first->id] != -1 && positions[second->id] != -1);

        if (first == second)
            return;
        std::swap(heap[positions[first->id]], heap[positions[second->id]]);
        std::swap(positions[first->id], positions[second->id]);
    }

    int size;
    std::vector<City *> heap;
};

#endif // HEAP_HPP
