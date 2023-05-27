#if !defined(ZIP_HPP)
#define ZIP_HPP

#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct Zip
{
    struct Node
    {
        Node() = default;
        Node(int code, std::string name, int pop) : code(code), name(name), pop(pop) {}

        int code;
        std::string name;
        int pop;
    };

    Zip(std::string filename)
    {
        std::ifstream file(filename);

        std::string line;

        while (std::getline(file, line))
        {
            std::stringstream row(line);

            std::string locname, tmp;

            std::getline(row, tmp, ',');
            tmp.replace(3, 1, ""); // replacing ' ' with ''
            int zip = std::stoi(tmp);

            std::getline(row, locname, ',');
            std::getline(row, tmp, ',');

            int pop = std::stoi(tmp);

            // locs.push_back(Node(zip, tmp));
            data[zip] = Node{zip, locname, pop};
        }
    }

    inline Node lookup(int code) const
    {
        return data[code];
    }

    std::array<Node, 100000> data;
};

#endif // ZIP_HPP
