#include "Heap.hpp"
#include "Tree.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

int main(int argc, char *argv[])
{

    Heap heap(10);
    BinaryTree tree;

    hclock::time_point t1, t2;

    srand(time(NULL));

    int N = 10000;

    for (int i = 0; i < N; i++)
    {
        int value = rand() % (10 * N);

        // t1 = hclock::now();
        tree.add(value);
        // t2 = hclock::now();

        // int tree_dur = duration_cast<ns>(t2 - t1).count();

        // t1 = hclock::now();
        heap.add(value);
        // t2 = hclock::now();

        // int heap_dur = duration_cast<ns>(t2 - t1).count();

        // std::cout << tree_dur << " " << heap_dur << '\n';
    }

    for (int i = 0; i < N; i++)
    {
        t1 = hclock::now();
        tree.remove();
        t2 = hclock::now();

        int tree_dur = duration_cast<ns>(t2 - t1).count();

        t1 = hclock::now();
        heap.remove();
        t2 = hclock::now();

        int heap_dur = duration_cast<ns>(t2 - t1).count();

        std::cout << tree_dur << " " << heap_dur << '\n';
    }
    // for (int i = 0; i < N; i++)
    // {
    //     auto value = tree.remove();

    //     // std::cout << value.value_or(-696969) << '\n';
    // }

    return 0;
}
