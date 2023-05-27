#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

typedef std::chrono::high_resolution_clock hclock;

bool linear_search(const std::vector<int> &array, int key, bool sorted = false)
{
    for (const auto &elem : array)
    {
        if (elem == key)
            return true;
        if (sorted && elem > key)
            return false;
    }

    return false;
}



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int N = std::atoi(argv[1]);


    // TODO: use std::random instead of this
    srand(time(NULL));

    std::random_device rd;
    std::default_random_engine rng(rd());


    std::vector<int> unsorted(N);
    std::vector<int> sorted(N);

    // Filling the array

    // Range of element is
    // 0 to 10 * N
    
    
    int nxt = 0;
    for (auto &elem : sorted)
    {
        nxt += rand() % (10);
        elem = nxt;
    }

    unsorted = sorted;
    // shuffling the data so that we get the same values but unsorted
    std::shuffle(unsorted.begin(), unsorted.end(), rng);
    
    // now we want to run a linear search right?
    // and compare how well it behaves

    hclock::time_point t1, t2;

    long total_time;

    int iterations = 100;

    for (int i = 0; i < iterations; i++)
    {
        int key = rand() % (5 * N);

        t1 = hclock::now();
        auto result = linear_search(unsorted, key, false);
        t2 = hclock::now();

        //std::cout << "Found: " << result << '\n';
    
        auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        total_time += dt;
    }

    double average_time = (double)total_time / (double)iterations;


    std::cout << N << "  " << average_time << "  ";
    
    total_time = 0;

    for (int i = 0; i < iterations; i++)
    {
        int key = rand() % (5 * N);

        t1 = hclock::now();
        auto result = linear_search(sorted, key, true);
        t2 = hclock::now();
    
        auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        total_time += dt;
    }

    average_time = (double)total_time / (double)iterations;

    std::cout << average_time << "\n";


    return 0;
}
