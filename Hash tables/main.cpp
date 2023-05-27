#include "Zip.hpp"
#include "hashed.hpp"
#include <chrono>
#include <iostream>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

#define MAX 9675

int main(int argc, char *argv[])
{

    Zip zip("../postnummer.csv");

    int prime = 9767;

    BucketHashmap hashmap(prime);
    ArrayHashmap arr_hashmap(prime, MAX * 2);

    // construct the bucket hashmap
    for (int i = 0; i < zip.size; i++)
    {
        hashmap.add(zip.data[i]);
        arr_hashmap.add(zip.data[i]);
    }

    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {
        int ind = rand() % zip.size;
        auto elem = zip.data[ind];

        auto t1 = hclock::now();
        std::cout << hashmap.lookup(elem.code).pop << '\n';
        auto t2 = hclock::now();

        std::cout << "Buckets: " << duration_cast<us>(t2 - t1).count() << '\n';

        t1 = hclock::now();
        std::cout << arr_hashmap.lookup(elem.code).pop << '\n';
        t2 = hclock::now();

        std::cout << "Arrays: " << duration_cast<us>(t2 - t1).count() << '\n';
    }

    // auto t1 = hclock::now();
    // std::cout << hashmap.lookup(11137).pop << '\n';
    // auto t2 = hclock::now();

    // int dur = duration_cast<ns>(t2 - t1).count();

    // std::cout << dur << '\n';

    return 0;
}
