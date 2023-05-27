#if !defined(NODE_HPP)
#define NODE_HPP

#include <cstdint>
#include <iostream>

struct Node
{
    int value = INT32_MAX; // default value
    Node *head = nullptr;

    inline Node *getCurrentHead()
    {
        auto nxt = this;

        // traverse to the next value
        while (nxt->head != nullptr)
        {
            nxt = nxt->head;
        }

        return nxt;
    }

    void append(Node *list)
    {
        auto *nxt = getCurrentHead();

        nxt->head = list;
    }

    // void insertAt(Node *node, Node *list)
    // {
    //     // this is not a doubly linked list, so don't you go tryinig to insert in the middle

    //     if (node->head != nullptr)
    //     {
    //         auto *tmp = node->head;
    //         auto *listHead = list->getCurrentHead();
    //         // node->head = list;
    //         listHead->head = tmp;
    //     }
    //     node->head = list;
    // }

    // push and get currentHead;
    // Node *push(int n)
    // {
    //     auto nxt = getCurrentHead();

    //     auto *node = new Node;
    //     node->value = n;

    //     nxt->head = node;

    //     return node;
    // }

    [[maybe_unused]] Node *push(int n, Node *curHead = nullptr)
    {
        auto *newNode = new Node;
        newNode->value = n;

        if (curHead == nullptr)
            curHead = getCurrentHead();

        if (curHead->head != nullptr)
        {
            std::cerr << "Trying to push in between elements, this is not supported yet\n";
            exit(1);
        }

        curHead->head = newNode;

        return newNode; // return new head
    }

    void print()
    {
        auto cur = this;
        std::cout << "[ ";

        do
        {
            std::cout << cur->value << ", ";
            cur = cur->head;
        } while (cur != nullptr);

        std::cout << " ]\n";
    }

    static void clear(Node *n)
    {
        // delete all subsequent elements
        while (n != nullptr) // points to a valid object
        {
            // std::cout << "Deleting a node with value " << n->value << '\n';
            auto *tmp = n;
            n = tmp->head;
            delete tmp;
        }
    }

    ~Node() = default;
};

#endif // NODE_HPP
