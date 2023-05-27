#if !defined(DIJKSTRA_HPP)
#define DIJKSTRA_HPP

#include "Entry.hpp"
#include "Heap.hpp"
#include <vector>

class Dijkstra
{
public:
    Dijkstra(int numOfCities) : heap(numOfCities)
    {
        wall.resize(numOfCities);
    }

    Entry shortest(City *to)
    {
        while (true)
        {
            // Step 1. Remove the first element;
            Entry current = heap.remove();

            // If we're there, return.
            if (current.city->id == to->id)
            {
                return current;
            }

            // Step 2. Traverse children
            for (auto &connection : current.city->neighbors)
            {
                int curDistance = connection.distance + current.traversed;
                Entry childEntry(connection.city);
                childEntry.traversed = curDistance;
                // cameFrom faces a problem: where do we store all those entries so
                // that they don't go out of scope?

                // Question: wall or queue first?

                // If it's already in the queue, compare distances
                if (heap.exists(connection.city->id))
                {
                    int heapInd = heap.positions[connection.city->id];

                    auto entry = heap.peek(heapInd);

                    // If the current path to the city is smaller,
                    // we update the Entry and bubble it up
                    if (entry.traversed > curDistance)
                    {
                        entry.cameFrom
                    }
                }
            }
        }
    }

    bool exists(int id) const
    {
        return !(wall[id].city->name.empty());
    }

public:
    Heap heap;

private:
    std::vector<Entry> wall;
};

#endif // DIJKSTRA_HPP
