#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    Map map("../trains.csv");

    std::cout << map.hash("Stockholm") << '\n';

    return 0;
}
