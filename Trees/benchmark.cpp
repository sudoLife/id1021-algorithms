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

template <typename T>
bool binary_search(const std::vector<T> &array, T key)
{
    int start = 0, stop = array.size() - 1;
    int mid;

    while (start != stop)
    {
        mid = (start + stop) / 2;

        T cur = array[mid];

        // printf("Looking for %d, mid element is %d, start = %d, stop = %d\n", key, cur, start, stop);

        if (cur == key)
        {
            // std::cout << "Found " << key << " at " << start << '\n';
            return true;
        }
        if (cur < key)
        {
            start = mid + 1;
        }
        else
        {
            stop = mid;
        }
    }

    // std::cout << "Found " << key << " at " << start << '\n';
    return (array[start] == key);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <N>\n";
        return 1;
    }

    int N = std::atoi(argv[1]);

    srand(time(NULL));

    BinaryTree<int> tree;

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

    // Now we can compare
    int iterations = 10;

    hclock::time_point t1, t2;

    double avg_tree = 0, avg_arr = 0;

    for (int i = 0; i < iterations; i++)
    {
        int elem = sorted[rand() % N];

        t1 = hclock::now();
        tree.lookup(elem);
        t2 = hclock::now();

        avg_tree += duration_cast<ns>(t2 - t1).count();

        t1 = hclock::now();
        binary_search(sorted, elem);
        t2 = hclock::now();

        avg_arr += duration_cast<ns>(t2 - t1).count();
    }

    avg_tree /= (double)iterations;
    avg_arr /= (double)iterations;

    std::cout << N << " " << avg_tree << " " << avg_arr << '\n';

    return 0;
}
