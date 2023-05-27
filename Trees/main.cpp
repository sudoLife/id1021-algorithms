#include "Tree.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

void fill_tree(BinaryTree<int> &tree, int N)
{
    srand(time(NULL));

    std::vector<int> sorted(N);

    int current = 0;

    for (int i = 0; i < N; i++)
    {
        sorted[i] = current;
        current += rand() % N;
    }

    std::vector<int> unsorted = sorted;

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(unsorted.begin(), unsorted.end(), g);

    for (const auto &elem : unsorted)
    {
        tree.add(elem, elem);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <N>\n";
        return 1;
    }

    int N = std::atoi(argv[1]);
    // int N = 10;
    BinaryTree<int> tree;

    fill_tree(tree, N);
    // std::vector<int> values({500, 400, 300, 450, 425, 470, 600, 550, 650});

    // for (auto value : values)
    // {
    //     tree.add(value, value);
    // }

    // tree.print();
    // std::cout << '\n';

    for (auto elem : tree)
    {
        std::cout << elem->value << ' ';
    }

    std::cout << '\n';

    // for (auto it = tree.begin(); it != tree.end(); it++)
    // {
    //     std::cout << (*it)->value << ' ';
    // }

    return 0;
}
