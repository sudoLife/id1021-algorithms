#include "Map.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

int shortest(City *from, City *to, int max)
{
    if (max < 0)
        return -1;

    if (from->name == to->name)
    {
        return 0;
    }

    int shortest_distance = max;

    for (const auto &connection : from->neighbors)
    {
        int cur_distance = connection.distance;
        int cur_result = shortest(connection.city, to, shortest_distance - cur_distance);

        if (cur_result < 0) // not adding it to statistics
            continue;

        cur_distance += cur_result;

        if (cur_distance < shortest_distance)
            shortest_distance = cur_distance;
    }

    if (shortest_distance == max) // we didn't find anything
        return -1;

    return shortest_distance;
}

struct Test
{
    Test(std::string from, std::string to) : from(from), to(to) {}
    std::string from;
    std::string to;
};

typedef std::chrono::high_resolution_clock hclock;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;
using std::chrono::duration_cast;

int main(int argc, char const *argv[])
{
    Map map("../trains.csv");

    std::vector<Test> tests;
    // tests.emplace_back("Stockholm", "Kiruna");
    tests.emplace_back("Malmö", "Göteborg");
    tests.emplace_back("Göteborg", "Stockholm");
    tests.emplace_back("Malmö", "Stockholm");
    // tests.emplace_back("Stockholm", "Sundsvall");
    // tests.emplace_back("Stockholm", "Umeå");
    // tests.emplace_back("Göteborg", "Sundsvall");
    // tests.emplace_back("Sundsvall", "Umeå");
    // tests.emplace_back("Umeå", "Göteborg");
    tests.emplace_back("Göteborg", "Umeå");

    hclock::time_point t1, t2;

    for (const auto &test : tests)
    {
        t1 = hclock::now();
        auto result = shortest(map.lookup(test.from), map.lookup(test.to), 2000);
        t2 = hclock::now();

        auto bm = duration_cast<us>(t2 - t1).count();
        std::cout << test.from << " to " << test.to << " in " << result << ", found in " << bm << " us\n";
    }

    return 0;
}
