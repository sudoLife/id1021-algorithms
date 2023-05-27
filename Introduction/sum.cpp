#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int benchmark_sum(unsigned int *indices, int *values, int n)
{

    int sum = 0;

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        sum += values[indices[i]];
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    double delta_duration = (double)duration / (double)n;

    printf("Access %d: %f ns\n", n, delta_duration * 1e3);

    return sum;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n>\n";

        return 1;
    }

    int n = std::atoi(argv[1]);

    std::vector<unsigned int> indices(n);
    std::vector<int> values(n);

    // Generating the array

    for (int i = 0; i < n; i++)
    {
        if (i % 2)
        {
            values[i] = -i;
        }
        else
        {
            values[i] = i;
        }
    }

    // Generating indices
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        indices[i] = rand() % n;
    }

    auto result = benchmark_sum(indices.data(), values.data(), n);

    std::cout << "Resulting sum is " << result << "\n";

    return 0;
}
