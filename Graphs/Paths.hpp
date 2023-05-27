#if !defined(PATHS_HPP)
#define PATHS_HPP

#include <iostream>
#include <optional>
#include <vector>

#include "City.hpp"

#define MAX_CITIES 54
class Paths
{
public:
    Paths()
    {
        path.reserve(MAX_CITIES);
    }
    std::optional<int> shortest(City *from, City *to, int max = 1e9)
    {
        if (max < 0)
            return std::nullopt;

        if (from == to)
            return std::optional<int>(0);

        // if we already tried this city, don't try any more
        for (const auto city : path)
        {
            if (city == from)
                return std::nullopt;
        }

        path.push_back(from);

        int shortest_path = max;
        for (auto &connection : from->neighbors)
        {
            auto res_ = shortest(connection.city, to, shortest_path - connection.distance);

            if (!res_.has_value())
                continue;

            int res = res_.value() + connection.distance;

            if (res < shortest_path)
            {
                shortest_path = res;
            }
        }

        path.pop_back();

        if (shortest_path == max) // we haven't found anything useful
            return std::nullopt;

        return std::optional<int>(shortest_path);
    }

    std::vector<City *> path;
    int shortest_path;
};

#endif // PATHS_HPP
