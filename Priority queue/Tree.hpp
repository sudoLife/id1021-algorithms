#if !defined(TREE_HPP)
#define TREE_HPP

#include <optional>

// TODO: make private members private
class BinaryTree
{
public:
    struct Node
    {
        Node(int key) : key(key), children(0) {}

        int key;
        int children;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    BinaryTree() = default;

    [[maybe_unused]] int add(int key)
    {
        // easiest scenario
        if (empty())
        {
            root = new Node(key);
            return 0;
        }

        auto *cur = root;
        auto curKey = key;

        int depth = 0;

        while (true)
        {
            cur->children++;

            if (curKey < cur->key)
            {
                std::swap(cur->key, curKey);
            }

            if (cur->left == nullptr)
            {
                cur->left = new Node(curKey);
                break;
            }

            if (cur->right == nullptr)
            {
                cur->right = new Node(curKey);
                break;
            }

            if (cur->left->children < cur->right->children)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
            depth++;
        }

        return depth;
    }

    std::optional<int> remove()
    {
        if (empty())
        {
            return std::nullopt;
        }

        auto retvalue = std::optional<int>(root->key);

        if (root->children == 0)
        {
            delete root;
            root = nullptr;
            return retvalue;
        }

        // easy cases are over.
        auto *cur = root;
        auto oldRoot = root;

        while (true)
        {
            cur->children--;
            if (cur->left == nullptr)
            {
                cur->key = cur->right->key;
                if (cur->right->children == 0)
                {
                    delete cur->right;
                    cur->right = nullptr;
                    return retvalue;
                }
                cur = cur->right;
                continue;
            }

            if (cur->right == nullptr)
            {
                cur->key = cur->left->key;
                if (cur->left->children == 0)
                {
                    delete cur->left;
                    cur->left = nullptr;
                    return retvalue;
                }
                cur = cur->left;
                continue;
            }
            if (cur->right->key < cur->left->key)
            {
                cur->key = cur->right->key;
                if (cur->right->children == 0)
                {
                    delete cur->right;
                    cur->right = nullptr;
                    return retvalue;
                }
                cur = cur->right;
                continue;
            }
            else
            {
                cur->key = cur->left->key;
                if (cur->left->children == 0)
                {
                    delete cur->left;
                    cur->left = nullptr;
                    return retvalue;
                }
                cur = cur->left;
                continue;
            }
        }

        delete oldRoot;
        return std::optional<int>(retvalue);
    }

    int push(int incr)
    {
        root->key += incr;

        // no need to do anything
        if (root->children == 0)
            return 0;

        auto *cur = root;
        int depth = 0;

        while (true)
        {
            if (cur->left && cur->right)
            {
                auto *minEl = min(cur->left, cur->right, cur);

                if (cur == minEl)
                {
                    return depth;
                }

                std::swap(cur->key, minEl->key);

                cur = minEl;
                depth++;
                continue;
            }

            if (cur->left && cur->key > cur->left->key)
            {
                std::swap(cur->key, cur->left->key);
                cur = cur->left;
                depth++;
                continue;
            }
            if (cur->right && cur->key > cur->right->key)
            {
                std::swap(cur->key, cur->right->key);
                cur = cur->right;
                depth++;
                continue;
            }

            break;
        }

        return depth;
    }

    inline bool empty() const
    {
        return root == nullptr;
    }

    ~BinaryTree()
    {
        recursiveDelete(root);
    }

private:
    void recursiveDelete(Node *&node)
    {
        if (node == nullptr)
            return;

        recursiveDelete(node->left);
        recursiveDelete(node->right);

        delete node;
    }

    inline Node *min(Node *x, Node *y, Node *z)
    {
        if (x->key <= y->key)
        {
            // x < y && x < z
            if (x->key <= z->key)
                return x;
            return z;
        }
        if (y->key <= z->key)
        {
            return y;
        }

        return z;
    }

private:
    Node *root = nullptr;
};

#endif // TREE_HPP
