#if !defined(ENTRY_HPP)
#define ENTRY_HPP

#include "City.hpp"

struct Entry
{
    Entry(City *city) : city(city) {}

    City *city = nullptr;
    Entry *cameFrom = nullptr;
    int traversed = 0;
};

#endif // ENTRY_HPP