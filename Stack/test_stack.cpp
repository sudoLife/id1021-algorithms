#include "dynamic_stack.hpp"
#include "static_stack.hpp"
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock hclock;

int main()
{
    int N = 20000;

    DynamicStack dstack(4);
    StaticStack sstack(N);

    hclock::time_point t1, t2;

    for (int i = 0; i < N; i++)
    {
        t1 = hclock::now();
        sstack.push(i);
        t2 = hclock::now();
        auto s_dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        t1 = hclock::now();
        dstack.push(i);
        t2 = hclock::now();
        auto d_dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        std::cout << i << " " << s_dur << " " << d_dur << "\n";
    }

    int sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += sstack.pop();
    }

    // printf("%d\n", sum);

    return 0;
}
