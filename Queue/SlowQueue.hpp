#if !defined(SLOW_QUEUE_HPP)
#define SLOW_QUEUE_HPP

#include <iostream>

template <typename T>
class SlowQueue
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
        }
        else
        {
            auto *cur = queue;

            while (cur->head != nullptr)
            {
                cur = cur->head;
            }

            cur->head = new Node(item);
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

        delete tmp; // no memory leaks on my watch
        return val;
    }

    bool empty()
    {
        return queue == nullptr;
    }

    ~SlowQueue()
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
};

#endif // SLOW_QUEUE_HPP
