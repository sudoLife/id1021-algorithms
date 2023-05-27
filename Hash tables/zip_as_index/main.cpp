#include "Zip.hpp"
#include <chrono>
#include <iostream>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

int main()
{
    Zip zip("../postnummer.csv");

    // std::cout << zip.linear("111 15").name << '\n';
    // std::cout << zip.binary("111 15").name << '\n';
    std::vector<int> searchItems({11115, 99499});

    hclock::time_point t1, t2;

    int N = 10;

    for (auto item : searchItems)
    {
        double total = 0;

        for (int i = 0; i < N; i++)
        {
            Zip::Node res;
            t1 = hclock::now();
            res = zip.lookup(item);
            t2 = hclock::now();

            total += duration_cast<us>(t2 - t1).count();
        }
        std::cout << "Total: " << total / N << '\n';
    }

    return 0;
}
