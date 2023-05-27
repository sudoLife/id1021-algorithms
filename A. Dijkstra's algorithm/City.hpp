#if !defined(CITY_HPP)
#define CITY_HPP

#include "Connection.hpp"
#include <string>
#include <vector>

// London City, far from pretty, 2005
struct City
{
    City() = default;
    City(std::string name, int id = 0) : name(name), id(id) {}
    void add(City *destination, int distance)
    {
        neighbors.emplace_back(destination, distance);
    }
    int id;
    int traversed = 0;
    City *prev = nullptr;
    std::string name;
    std::vector<Connection> neighbors;
};

#endif // CITY_HPP
