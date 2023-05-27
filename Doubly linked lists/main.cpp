#include "DoubleNode.hpp"
#include "Node.hpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <unordered_set>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }

    int N = std::atoi(argv[1]);

    std::vector<DoubleNode *> d_refs(N);
    std::vector<Node *> s_refs(N);

    auto *d_node = new DoubleNode;
    auto *s_node = new Node;

    d_node->value = 0;
    s_node->value = 0;

    DoubleNode *dcurHead = d_node;
    Node *scurHead = s_node;

    d_refs[0] = dcurHead;
    s_refs[0] = scurHead;

    for (int i = 1; i < N; i++)
    {
        dcurHead = d_node->push(i, dcurHead);
        d_refs[i] = dcurHead;

        scurHead = s_node->push(i, scurHead);
        s_refs[i] = scurHead;
    }

    // Now we have memory addresses and can start deleting

    // let's delete a quarter of the elements and estimate the time it takes to do so.
    srand(time(NULL));

    std::unordered_set<int> indices;

    for (int i = 0; i < N; i++)
    {
        indices.insert(rand() % N);
    }

    // Now we can start deleting
    hclock::time_point t1, t2;
    double d_total_time = 0;
    double s_total_time = 0;

    for (const auto &index : indices)
    {
        // std::cout << " Deleting node " << index << '\n';
        auto *d_elem = d_refs[index];
        auto *s_elem = s_refs[index];

        t1 = hclock::now();
        DoubleNode::pop(d_node, d_elem);
        t2 = hclock::now();

        d_total_time += duration_cast<ns>(t2 - t1).count();

        // used-to-be first element
        if (d_elem->prev == nullptr)
        {
            d_elem->next->prev = d_elem;
            d_node = d_elem;
        }
        else
        {

            if (d_elem->next != nullptr)
            {
                d_elem->next->prev = d_elem;
            }

            d_elem->prev->next = d_elem;
        }

        t1 = hclock::now();
        Node::pop(s_node, s_elem);
        t2 = hclock::now();

        s_total_time += duration_cast<ns>(t2 - t1).count();

        // first item in the list
        if (s_elem->head == s_node)
        {
            s_node = s_elem;
        }
        else
        {
            auto *cur = s_node;
            // assuming it's in the list
            while (cur->head != s_elem->head && cur->head != nullptr)
            {
                cur = cur->head;
            }
            // putting it back
            cur->head = s_elem;
        }
    }

    std::cout << N
              << " " << d_total_time / indices.size()
              << " " << s_total_time / indices.size()
              << '\n';

    DoubleNode::clear(d_node);
    Node::clear(s_node);

    return 0;
}
