#include "Dijkstra.hpp"
#include "Map.hpp"
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock hclock;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;
using std::chrono::duration_cast;

int main()
{
    Map map("../trains.csv");

    int numOfCities = map.id;

    std::string from = "Malmö";
    std::string to = "Kiruna";

    Dijkstra dijkstra(map, numOfCities);

    auto t1 = hclock::now();
    City *result = dijkstra.shortest(from, to);
    auto t2 = hclock::now();

    std::cout << "Benchmark: " << duration_cast<us>(t2 - t1).count() << '\n';

    // std::cout << result->traversed << '\n';
    while (result != nullptr)
    {
        std::cout << result->name << "\n  ||  \n";
        result = result->prev;
    }

    return 0;
}
