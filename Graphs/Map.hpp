#if !defined(MAP_HPP)
#define MAP_HPP

#include "City.hpp"
#include "fstream"
#include <cassert>
#include <filesystem>
#include <optional>
#include <sstream>
#include <vector>

class Map
{
public:
    Map(std::string filename)
    {
        std::ifstream input(filename);
        cities.resize(mod);

        if (!std::filesystem::exists(std::filesystem::path(filename)))
        {
            throw std::runtime_error("Specified file does not exist");
        }

        std::string line;
        while (std::getline(input, line))
        {
            // each line contains three fields: City, City, distance (mins)
            std::stringstream stream(line);

            std::string city1, city2, sdist;

            std::getline(stream, city1, ',');
            std::getline(stream, city2, ',');
            std::getline(stream, sdist, ',');
            int distance = std::stoi(sdist);

            // lookup two cities and add a connection
            auto first = lookup(city1);

            if (first == nullptr)
            {
                first = &add(city1);
            }

            auto second = lookup(city2);

            if (second == nullptr)
            {
                second = &add(city2);
            }

            first->add(second, distance);
            second->add(first, distance);
        }
    }

    // adds a city and returns its index
    // presumes no collisions
    City &add(std::string name)
    {
        int index = hash(name);

        while (!cities[index].name.empty())
        {
            index++;
        }

        assert(index < cities.size());

        cities[index].name = name;
        return cities[index];
    }

    City *lookup(std::string name)
    {
        int index = hash(name);

        while (cities[index].name != name && index < cities.size())
        {
            index++;
        }

        return index < cities.size() ? &cities[index] : nullptr;
    }

    int hash(std::string name)
    {
        int hash = 7;
        for (int i = 0; i < name.length(); i++)
        {
            // we get negative characters due to utf-8, hopefully this will work
            hash = (hash * 31 % mod) + std::abs(name[i]);
        }

        return hash % mod;
    }

public:
    std::vector<City> cities;

private:
    const int mod = 541;
};

#endif // MAP_HPP
