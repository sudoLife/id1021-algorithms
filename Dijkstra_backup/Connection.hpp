#if !defined(CONNECTION_HPP)
#define CONNECTION_HPP

#include "City.hpp"

// forward declaration, because we have a circular dependency
class City;

class Connection
{
public:
    Connection(City *city, int distance) : city(city), distance(distance) {}

public:
    City *city;
    int distance; // distance in mins
};

#endif // CONNECTION_HPP