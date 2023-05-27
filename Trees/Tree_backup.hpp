#if !defined(TREE_HPP)
#define TREE_HPP

#include <optional>

template <typename T>
class BinaryTree
{
    struct Node
    {
        int key;
        T value;

        Node *left = nullptr;
        Node *right = nullptr;

        Node() = default;
        Node(int key, T value)
        {
            this->key = key;
            this->value = value;
        }
    };

public:
    BinaryTree() : root(nullptr){};

    void add(int key, T value)
    {
        if (root == nullptr)
        {
            root = new Node(key, value);
            // root->key = key;
            // root->value = value;
        }
        else
        {
            // traverse the tree until we hit the right place
            Node *cur = root;
            while (true)
            {
                // update
                if (cur->key == key)
                {
                    cur->value = value;
                    break;
                }

                Node *&direction = cur->key > key ? cur->left : cur->right;

                if (direction != nullptr)
                {
                    cur = direction;
                    continue;
                }

                // found the end
                direction = new Node(key, value);
                break;
            }
        }
    }

    std::optional<T> lookup(int key)
    {
        if (root == nullptr)
            return std::nullopt;

        Node *cur = root;

        while (true)
        {
            if (cur->key == key)
            {
                return std::make_optional<T>(cur->value);
            }

            Node *direction = cur->key > key ? cur->left : cur->right;

            // end of the road
            if (direction == nullptr)
            {
                return std::nullopt;
            }

            cur = direction;
        }
    }

    ~BinaryTree()
    {
        // we have to traverse the tree and erase them all
        // one way to do that would be to traverse it and
        // add pointers to each element to an array
        // but that's kinda whack
        // I wanna try using smart pointers for that
    }

private:
    Node *root;
};

#endif // TREE_HPP
