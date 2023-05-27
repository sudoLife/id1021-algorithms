#include <cstdint>
#include <iostream>

#if !defined(DOUBLE_NODE_HPP)
#define DOUBLE_NODE_HPP

struct DoubleNode
{
    int value = INT32_MAX;
    DoubleNode *prev = nullptr;
    DoubleNode *next = nullptr;

    inline DoubleNode *getCurrentHead()
    {
        auto nxt = this;

        // traverse to the next value
        while (nxt->next != nullptr)
        {
            nxt = nxt->next;
        }

        return nxt;
    }

    [[maybe_unused]] DoubleNode *push(int n, DoubleNode *curHead = nullptr)
    {
        auto *newNode = new DoubleNode;
        newNode->value = n;

        if (curHead == nullptr)
            curHead = getCurrentHead();

        if (curHead->next != nullptr)
        {
            std::cerr << "Trying to push in between elements, this is not supported yet\n";
            exit(1);
        }

        curHead->next = newNode;
        newNode->prev = curHead;

        return newNode;
    }

    // NOTE: this doesn't delete the element itself
    static void pop(DoubleNode *&node, DoubleNode *elem)
    {
        /// first element
        if (node == elem && node->prev == nullptr)
        {
            node = node->next;
            node->prev = nullptr;
            return;
        }

        elem->prev->next = elem->next;
        if (elem->next != nullptr)
        {
            elem->next->prev = elem->prev;
        }
    }

    static void print(DoubleNode *node)
    {
        auto tmp = node;
        while (tmp != nullptr)
        {
            std::cout << tmp->value << " ";
            tmp = node->next;
        }
    }

    static void clear(DoubleNode *node)
    {
        // assuming it's the first node for simplicity
        // delete all subsequent elements
        while (node != nullptr) // points to a valid object
        {
            // std::cout << "Deleting a node with value " << node->value << '\n';
            auto *tmp = node;
            node = tmp->next;
            delete tmp;
        }
    }
};

#endif // DOUBLE_NODE_HPP
