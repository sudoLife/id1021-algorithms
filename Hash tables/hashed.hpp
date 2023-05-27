#if !defined(HASHED_HPP)
#define HASHED_HPP

#include "Zip.hpp"
#include <cassert>
#include <vector>

typedef Zip::Node Node;

class ArrayHashmap
{
public:
    ArrayHashmap(int hash, int max) : hash(hash)
    {
        container.resize(max);
    }

    void add(Node element)
    {
        auto index = hashf(element.code);

        while (!container[index].name.empty())
        {
            index++;
        }
        container[index] = element;
    }

    Node lookup(int code)
    {
        int index = hashf(code);

        // TODO: Mention that this decays into linear search if there is no element or we are too dense.
        while (container[index].name != "" && container[index].code != code && index < container.size())
        {
            index++;
        }

        std::cout << "Array Depth: " << index - hashf(code) << '\n';
        return index < container.size() ? container[index] : Node();
    }

private:
    inline int hashf(int key) { return key % hash; }

    std::vector<Node> container;
    int hash;
};

class BucketHashmap
{
public:
    struct Bucket
    {
        Bucket() = default;
        Bucket(Node value) : value(value) {}

        Node value;
        Bucket *next = nullptr;
    };

    BucketHashmap(int hash) : hash(hash)
    {
        container.resize(hash);
    }

    void add(Node value)
    {
        int index = hashf(value.code);
        if (container[index].value.name == "") // empty node
        {
            container[index].value = value;
            return;
        }

        Bucket *&cur = container[index].next;
        while (cur != nullptr)
        {
            cur = cur->next;
        }

        cur = new Bucket(value);
    }

    Node lookup(int code)
    {
        int index = hashf(code);

        Bucket *cur = &container[index];

        int depth = 0;
        do
        {
            if (cur->value.code == code)
            {
                std::cout << "Bucket Depth: " << depth << '\n';
                return cur->value;
            }

            cur = cur->next;
            depth++;
        } while (cur != nullptr);

        return Node();
    }

    ~BucketHashmap()
    {
        for (auto &elem : container)
        {
            auto *cur = elem.next;

            while (cur != nullptr)
            {
                auto *old = cur;
                cur = cur->next;
                delete old;
            }
        }
    }

private:
    int hash;
    std::vector<Bucket> container;

    inline int hashf(int key) const { return key % hash; }
};

#endif // HASHED_HPP
