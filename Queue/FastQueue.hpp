#if !defined(FAST_QUEUE_HPP)
#define FAST_QUEUE_HPP

#include <iostream>

template <typename T>
class FastQueue
{
    struct Node
    {
        T item;
        Node *head = nullptr;

        Node(T item) : item(item) {}
    };

public:
    // same as add() operation in the assignment PDF
    void push(T item)
    {
        if (queue == nullptr)
        {
            queue = new Node(item);
            last = queue;
        }
        else
        {
            last->head = new Node(item);
            last = last->head;
        }
    }

    // same as remove() operation in the assignment PDF
    [[maybe_unused]] T pop()
    {
        if (this->empty())
            throw std::runtime_error("Pop from an empty queue");

        auto val = queue->item;
        auto *tmp = queue;
        queue = queue->head;

        if (last == tmp) // we now have an empty queue
        {
            last = nullptr;
        }

        delete tmp; // no memory leaks on my watch
        return val;
    }

    bool empty()
    {
        return queue == nullptr;
    }

    ~FastQueue()
    {
        while (queue != nullptr)
        {
            pop();
        }
    }

    void print()
    {
        auto *cur = queue;

        while (cur != nullptr)
        {
            std::cout << cur->item << " ";
            cur = cur->head;
        }
    }

private:
    Node *queue = nullptr;
    Node *last = nullptr;
};

#endif // FAST_QUEUE_HPP
