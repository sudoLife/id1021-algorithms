#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int element_num = std::atoi(argv[1]);

    int k = 100; // Checking the search 10000 times

    std::vector<int> keys(element_num);
    std::vector<int> values(element_num);

    srand(time(NULL));

    long t_total = 0;

    for (int j = 0; j < k; j++)
    {
        // fill the keys array with random number from 0 to 10*n
        for (auto &key : keys)
        {
            key = rand() % (10 * element_num);
        }

        // fill the array with with random number from 0 to 10*n
        for (auto &value : values)
        {
            value = rand() % (10 * element_num);
        }

        auto t1 = std::chrono::high_resolution_clock::now();

        int duplicate_num = 0;

        for (const auto key : keys)
        {
            for (const auto value : values)
            {
                if (key == value)
                {
                    duplicate_num++;
                    break;
                }
            }
        }
        
        auto t2 = std::chrono::high_resolution_clock::now();
        t_total += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << "Found " << duplicate_num << " duplicates\n";

    }

    printf("%d %f\n", element_num, t_total / (double)k);

    return 0;
}
