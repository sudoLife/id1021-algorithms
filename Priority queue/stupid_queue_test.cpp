#include "stupid_queue.hpp"
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

    auto N = std::atoi(argv[1]);

    StupidQueueRemove rqueue;
    StupidQueueAdd aqueue;
    std::vector<int> values(N);

    for (int i = 0; i < N; i++)
    {
        values[i] = rand() % N;
    }

    srand(time(NULL));

    hclock::time_point t1, t2;

    long pushes_count = 0;

    for (int i = 0; i < N; i++)
    {
        t1 = hclock::now();
        rqueue.push(values[i]);
        t2 = hclock::now();
        pushes_count += duration_cast<us>(t2 - t1).count();

        aqueue.push(values[i]);
    }

    long pops_count = 0;

    for (int i = 0; i < N; i++)
    {
        t1 = hclock::now();
        auto val = aqueue.pop();
        t2 = hclock::now();
        pops_count += duration_cast<us>(t2 - t1).count();
    }

    // aqueue.list.print();

    std::cout << N << ' ' << pushes_count << ' ' << pops_count << '\n';

    return 0;
}
