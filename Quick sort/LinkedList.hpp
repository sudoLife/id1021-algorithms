#if !defined(LINKED_LIST_HPP)
#define LINKED_LIST_HPP

#include <cassert>
#include <iostream>

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T value;
        Node *next = nullptr;

        Node(T value, Node *next = nullptr) : value(value), next(next) {}

        static inline void swap(Node *i, Node *j)
        {
            if (i == j)
                return;
            auto temp = i->value;
            i->value = j->value;
            j->value = temp;
        }
    };

    Node *first = nullptr;
    Node *last = nullptr;

    // now we should make methods to actually construct this
    LinkedList(bool child = false) : child(child) {}

    ~LinkedList()
    {
        // do nothing if we're a child of some bigger node
        if (child)
            return;

        auto cur = first;

        while (cur != nullptr)
        {
            auto temp = cur;
            cur = cur->next;
            delete temp;
        }
    }

    void append(T value)
    {
        auto newNode = new Node(value);
        if (first == nullptr)
        {
            first = newNode;
        }
        if (last != nullptr)
        {
            last->next = newNode;
        }
        last = newNode;
    }

    void print()
    {
        auto cur = first;

        while (cur != nullptr)
        {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }

        std::cout << '\n';
    }

    static void quicksort(Node *start, Node *stop)
    {
        if (start != stop && stop->next != start)
        {
            Node *pivot = nullptr;
            Node *i_prev;
            // partitioning
            {
                auto *low = start;
                auto *high = stop;

                pivot = high;
                i_prev = low;
                Node *i = low;

                for (Node *j = low; j != high; j = j->next)
                {
                    if (j->value < pivot->value)
                    {
                        Node::swap(i, j);
                        i_prev = i;
                        i = i->next;
                    }
                }
                Node::swap(i, pivot);
                pivot = i;
            }
            quicksort(start, i_prev);
            quicksort(pivot->next, stop);
        }
    }

    // static void quicksort_old(Node *low, Node *high)
    // {
    //     // partitioning
    //     assert(low != nullptr && high != nullptr);
    //     auto *pivot = high;

    //     if (low != high) // more than 1 element
    //     {
    //         // 1. partition
    //         auto *pivot = high;
    //         std::cout << "Pivot: " << pivot->value << '\n';

    //         Node *i = low;
    //         Node *i_prev = low;
    //         Node *j = low;

    //         for (; j != pivot; j = j->next)
    //         {
    //             if (j->value < pivot->value)
    //             {
    //                 std::cout << "Swapping " << i->value << " with " << j->value << '\n';
    //                 Node::swap(i, j);
    //                 i_prev = i;
    //                 i = i->next;
    //             }
    //         }

    //         std::cout << "Swapping " << i->value << " with " << pivot->value << '\n';
    //         Node::swap(i, pivot);
    //         pivot = i;
    //         quicksort(low, i_prev);
    //         // this is the problematic line
    //         if (pivot->next != nullptr)
    //             quicksort(pivot->next, high);
    //     }
    // }

private:
    bool child;
};

#endif // LINKED_LIST_HPP
