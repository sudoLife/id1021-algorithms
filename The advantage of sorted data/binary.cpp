#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;

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
            return true;
        if (cur < key)
        {
            start = mid + 1;
        }
        else
        {
            stop = mid;
        }
    }

    return (array[start] == key);
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

    std::vector<int> sorted(N);

    int nxt = 0;

    for (auto &elem : sorted)
    {
        nxt += rand() % 10;
        elem = nxt;
    }

    // now we need to sort it.
    // std::sort(sorted.begin(), sorted.end());

    hclock::time_point t1, t2;
    int iterations = 100;

    long total_time = 0;
    int sum = 0;

    int max_time = 0;

    for (int i = 0; i < iterations; i++)
    {
        // int key = -1 * (rand() % (10 * N));
        int key = -100000;

        t1 = hclock::now();
        auto res = binary_search(sorted, key);
        // sum+= std::binary_search(sorted.begin(), sorted.end(), key);
        t2 = hclock::now();

        auto dt = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
        // std::cout << "dt : " << dt << "\n";

        total_time += dt;
        if (dt > max_time)
            max_time = dt;
    }

    double average_time = (double)total_time / (double)iterations;

    // std::cout << "Sum " << sum << "\n";

    std::cout << N << "  " << average_time << '\n';

    return 0;
}
