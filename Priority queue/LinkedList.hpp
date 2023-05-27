#if !defined(LINKED_LIST_HPP)
#define LINKED_LIST_HPP

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
    };

    Node *first = nullptr;
    Node *last = nullptr;

    ~LinkedList()
    {
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
            last = newNode;
            return;
        }

        last->next = newNode;
        last = newNode;
    }

    void print()
    {
        auto *cur = first;

        while (cur != nullptr)
        {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }

        std::cout << '\n';
    }
};

#endif // LINKED_LIST_HPP
