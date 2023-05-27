#if !defined(STUPID_QUEUE)
#define STUPID_QUEUE

#include "LinkedList.hpp"
#include <cassert>

class StupidQueueAdd
{
public:
    StupidQueueAdd() = default;
    typedef LinkedList<int>::Node Node;

    void push(int value)
    {
        list.append(value);
    }

    int pop()
    {
        // we have to find the smallest element and remove it.
        auto *smallest = list.first;
        Node *smallest_prev = nullptr;

        // only one element in the list
        if (smallest->next == nullptr)
        {
            auto value = smallest->value;
            delete smallest;
            list.first = nullptr;
            list.last = nullptr;

            return value;
        }

        Node *prev = smallest;
        Node *current = smallest->next;

        while (current != nullptr)
        {
            if (current->value < smallest->value)
            {
                smallest = current;
                smallest_prev = prev;
            }

            prev = current;
            current = current->next;
        }
        // we're the first
        if (smallest_prev != nullptr)
        {
            smallest_prev->next = smallest->next;
        }
        else
        {
            assert(smallest == list.first);
            list.first = list.first->next;
        }

        auto value = smallest->value;

        delete smallest;
        return value;
    }

    LinkedList<int> list;
};

class StupidQueueRemove
{
public:
    StupidQueueRemove() = default;
    typedef LinkedList<int>::Node Node;

    void push(int value)
    {
        auto *current = list.first;
        Node *prev = nullptr;

        auto *newNode = new Node(value);

        if (list.first == nullptr)
        {
            list.first = newNode;
            return;
        }

        while (current != nullptr)
        {
            if (value <= current->value)
            {
                if (prev == nullptr)
                {
                    assert(list.first == current);

                    newNode->next = list.first;
                    list.first = newNode;
                }
                else
                {
                    prev->next = newNode;
                    newNode->next = current;
                }
                return;
            }
            prev = current;
            current = current->next;
        }

        // we're the last
        prev->next = newNode;
    }
    // O(1)
    int pop()
    {
        auto value = list.first->value;
        auto *tmp = list.first;
        list.first = list.first->next;
        delete tmp;
        return value;
    }

    LinkedList<int> list;
};

#endif // STUPID_QUEUE
