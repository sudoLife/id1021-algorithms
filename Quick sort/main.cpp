#include "LinkedList.hpp"
#include "array_quicksort.hpp"
#include <algorithm>
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
    if (argc != 2)
    {
        return 1;
    }

    int N = std::atoi(argv[1]);

    srand(time(NULL));

    std::vector<int> arr(N);
    LinkedList<int> list;

    for (int i = 0; i < N; i++)
    {
        int value = rand() % N;
        arr[i] = value;
        list.append(value);
    }

    // std::cout << "Initial values: ";
    // list.print();

    hclock::time_point t1, t2;

    t1 = hclock::now();
    array::quicksort(arr, 0, arr.size() - 1);
    t2 = hclock::now();

    int array_us = duration_cast<us>(t2 - t1).count();

    t1 = hclock::now();
    LinkedList<int>::quicksort(list.first, list.last);
    t2 = hclock::now();

    int ll_us = duration_cast<us>(t2 - t1).count();

    std::cout << N << " " << array_us << " " << ll_us << '\n';

    return 0;
}
