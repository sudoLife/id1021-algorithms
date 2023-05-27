#include "Paths.hpp"
#include "Map.hpp"
#include <chrono>
#include <iostream>
#include <vector>

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

int main()
{
    Map map("../trains.csv");

    std::vector<Test> tests;

    // tests.emplace_back("Stockholm", "Kiruna");
    // tests.emplace_back("Malmö", "Göteborg");
    // tests.emplace_back("Göteborg", "Stockholm");
    // tests.emplace_back("Malmö", "Stockholm");
    // tests.emplace_back("Stockholm", "Sundsvall");
    // tests.emplace_back("Stockholm", "Umeå");
    // tests.emplace_back("Göteborg", "Sundsvall");
    // tests.emplace_back("Sundsvall", "Umeå");
    // tests.emplace_back("Umeå", "Göteborg");
    // tests.emplace_back("Göteborg", "Umeå");

    tests.emplace_back("Malmö", "Göteborg");
    tests.emplace_back("Malmö", "Stockholm");
    tests.emplace_back("Malmö", "Sundsvall");
    tests.emplace_back("Malmö", "Umeå");
    tests.emplace_back("Malmö", "Kiruna");
    hclock::time_point t1, t2;

    for (const auto &test : tests)
    {
        t1 = hclock::now();
        auto result = Paths().shortest(map.lookup(test.from), map.lookup(test.to), 20000);
        t2 = hclock::now();

        auto bm = duration_cast<us>(t2 - t1).count();
        std::cout << test.from << " to " << test.to << " in " << result.value_or(1e9) << ", found in " << bm << " us\n";
    }

    return 0;
}