#include "Dijkstra.hpp"
#include "Map.hpp"
#include <iostream>

int main()
{
    Map map("../trains.csv");

    int numOfCities = map.id;

    std::cout << numOfCities << '\n';

    std::string from = "Kiruna";
    std::string to = "Malmö";

    {
        Dijkstra dijkstra(numOfCities);
        dijkstra.heap.add(Entry(map.lookup(from)));
        dijkstra.shortest(map.lookup(to));
    }

    return 0;
}
