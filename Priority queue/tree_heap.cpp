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

    BinaryTree tree;
    int N = 128;
    int range = 200;

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        tree.add(rand() % range);
    }

    // for (int i = 0; i < N; i++)
    // {
    //     int elem = tree.remove().value();
    //     elem += rand() % 10 + 10;
    //     std::cout << tree.add(elem) << '\n';
    // }

    for (int i = 0; i < N; i++)
    {
        auto depth = tree.push(rand() % 10 + 10);
        std::cout << depth << '\n';
    }

    return 0;
}
