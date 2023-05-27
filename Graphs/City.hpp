#if !defined(CITY_HPP)
#define CITY_HPP

#include "Connection.hpp"
#include <string>
#include <vector>

// London City, far from pretty, 2005
class City
{
public:
    City() = default;
    City(std::string name) : name(name) {}
    // TODO: check if this is supposed to be reference or no
    void add(City *destination, int distance)
    {
        // this should check whether the destination exists?
        neighbors.emplace_back(destination, distance);
    }

public:
    std::string name;
    std::vector<Connection> neighbors;
};

#endif // CITY_HPP
