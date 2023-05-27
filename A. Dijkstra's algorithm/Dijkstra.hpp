#if !defined(DIJKSTRA_HPP)
#define DIJKSTRA_HPP

#include "Heap.hpp"
#include "Map.hpp"
#include <vector>

class Dijkstra
{
public:
    // copying the map cuz we're gonna do some nasty stuff
    Dijkstra(Map map, int numOfCities) : heap(numOfCities), map(map)
    {
        wall.resize(numOfCities, nullptr);
    }
    // returns a pointer to a populated city from which you can trace the whole path
    City *shortest(std::string from_, std::string to_)
    {
        // Step 0. Setup
        City *from = map.lookup(from_);
        City *to = map.lookup(to_);
        heap.add(from);
        wall[from->id] = from;
        while (true)
        {
            // Step 1. Remove the first element;
            if (heap.empty())
                return nullptr;
            City *parent = heap.remove();
            // If we're there, return.
            if (parent->id == to->id)
                return parent;
            // Step 2. Traverse children
            for (auto &connection : parent->neighbors)
            {
                int curDistance = connection.distance + parent->traversed;
                City *child = connection.city;
                // Check if child is on the wall already
                if (wall[child->id] != nullptr)
                {
                    // It's on the wall, but we found a shorter path
                    // Updating...
                    if (curDistance < child->traversed)
                    {
                        child->traversed = curDistance;
                        child->prev = parent;
                        // add or update if exists
                        heap.addOrBubble(child);
                    }
                }
                else
                {
                    // Adding to the wall
                    wall[child->id] = child;
                    // if it's not on the wall, it can't possibly be in queue.
                    child->traversed = curDistance;
                    child->prev = parent;
                    heap.add(child);
                }
            }
        }
    }

public:
    std::vector<City *> wall;

private:
    Heap heap;
    Map map;
};

#endif // DIJKSTRA_HPP
