#if !defined(TREE_HPP)
#define TREE_HPP

#include "FastQueue.hpp"
#include <iostream>
#include <memory>
#include <optional>

template <typename tree>
class TreeIterator
{
public:
    using ValueType = typename tree::ValueType;
    using PointerType = ValueType *;
    using Iterator = TreeIterator;

public:
    TreeIterator(PointerType root) : current(root)
    {
        if (current)
        {
            pushBranches();
        }
    }

    Iterator &operator++()
    {
        // // end()
        if (queue.empty())
        {
            current = nullptr;
        }

        // end of the road
        if (current == nullptr)
        {
            return *this;
        }

        current = queue.pop();
        pushBranches();

        return *this;
    }

    Iterator operator++(int)
    {
        auto iterator = *this;
        ++(*this);
        return iterator;
    }

    bool operator==(const Iterator &other) const
    {
        return current == other.current;
    }

    bool operator!=(const Iterator &other) const
    {
        return !(current == other.current);
    }

    PointerType
    operator*() const noexcept
    {
        return current;
    }

private:
    inline void pushBranches()
    {
        if (current->left)
        {
            queue.push(current->left.get());
        }

        if (current->right)
        {
            queue.push(current->right.get());
        }
    }

private:
    PointerType current;
    FastQueue<PointerType> queue;
};

template <typename T>
class BinaryTree
{
    struct Node
    {
        int key;
        T value;

        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};

        Node() = delete;
        Node(int key, T value) : key(key), value(value) {}
    };

public:
    using ValueType = Node;
    using Iterator = TreeIterator<BinaryTree<T>>;

    BinaryTree() = default;

    Iterator begin()
    {
        return Iterator(root.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    void print(Node *node = nullptr)
    {
        if (!node)
            node = root.get();

        if (node->left)
        {
            print(node->left.get());
        }

        std::cout << node->value << " ";

        if (node->right)
        {
            print(node->right.get());
        }
    }

    void add(int key, T value)
    {
        if (!root)
        {
            root = std::make_unique<Node>(key, value);
            return;
        }

        Node *cur = root.get();
        while (true)
        {
            // update
            if (cur->key == key)
            {
                cur->value = value;
                break;
            }
            // left branch
            if (cur->key > key)
            {
                if (!cur->left)
                {
                    cur->left = std::make_unique<Node>(key, value);
                    break;
                }
                else
                {
                    cur = cur->left.get();
                }
            }
            // right branch
            if (cur->key < key)
            {
                if (!cur->right)
                {
                    cur->right = std::make_unique<Node>(key, value);
                    break;
                }
                else
                {
                    cur = cur->right.get();
                }
            }
        }
    }

    std::optional<T> lookup(int key)
    {
        if (!root)
            return std::nullopt;

        Node *cur = root.get();

        while (true)
        {
            if (cur->key == key)
            {
                return std::make_optional<T>(cur->value);
            }

            Node *direction = cur->key > key ? cur->left.get() : cur->right.get();

            // end of the road
            if (direction == nullptr)
            {
                return std::nullopt;
            }

            cur = direction;
        }
    }

    ~BinaryTree() = default;

private:
    std::unique_ptr<Node> root{nullptr};
};

#endif // TREE_HPP
