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
    std::vector<int> sorted2(N);

    int nxt = 0;
    int nxt2 = 0;

    for (int i = 0; i < sorted.size(); i++)
    {
        nxt += rand() % 10;
        nxt2 += rand() % 10;

        sorted[i] = nxt;
        sorted2[i] = nxt2;
    }

    // now we need to sort it.
    // std::sort(sorted.begin(), sorted.end());

    hclock::time_point t1, t2;


    t1 = hclock::now();

    int sum = 0;
    int last_index = 0;
    for (int i = 0; i < sorted.size(); i++)
    {
        // sum += binary_search(sorted2, key);
        for (int j = last_index; j < sorted2.size(); j++)
        {
            if (sorted[i] <= sorted2[j])
            {
                sum += (sorted[i] == sorted[j]);
                // no need to start from the beginning
                last_index = j;
                break;
            }
        }
    }
    t2 = hclock::now();

    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << sum << " duplicates found\n";
    std::cout << N << "  " << dt << "\n";

    return 0;
}
