#if !defined(ZIP_HPP)
#define ZIP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct Zip
{
    struct Node
    {
        Node() = default;
        Node(std::string code, std::string name, int pop) : code(code), name(name), pop(pop) {}

        std::string code;
        std::string name;
        int pop;
    };

    Zip(std::string filename)
    {
        data = new Node[10000];

        std::ifstream file(filename);

        std::string line;

        int i = 0;

        while (std::getline(file, line))
        {
            std::stringstream row(line);

            std::string zip, locname, tmp;

            std::getline(row, zip, ',');

            std::getline(row, locname, ',');

            std::getline(row, tmp, ',');

            int pop = std::stoi(tmp);

            // locs.push_back(Node(zip, tmp));
            data[i++] = Node{zip, locname, pop};
        }

        size = i;
    }

    Node linear(std::string code)
    {
        for (int i = 0; i < size; i++)
        {
            if (!data[i].code.compare(code))
            {
                return data[i];
            }
        }

        return Node();
    }

    Node binary(std::string code)
    {
        int start = 0, stop = size - 1;
        int mid;

        while (start != stop)
        {
            mid = (start + stop) / 2;

            int res = code.compare(data[mid].code);

            if (res == 0)
            {
                return data[mid];
            }

            if (res > 0)
            {
                start = mid + 1;
            }
            else
            {
                stop = mid;
            }
        }

        return (!data[0].code.compare(code)) ? data[0] : Node();
    }

    ~Zip()
    {
        delete[] data;
    }

    Node *data = nullptr;
    int size;
};

#endif // ZIP_HPP
