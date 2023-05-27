#include "Zip.hpp"
#include <chrono>
#include <iostream>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

#define MAX 9675

void collisions(const std::string filename, int mod)
{
    std::vector<int> data(mod, 0);

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream row(line);

        std::getline(row, line, ','); // overwriting cuz idc

        int code = std::stoi(line);
        int index = code % mod;
        data[index]++;
    }

    // done with that, time to see how many collisions we've got
    // std::vector<int> cols(mod / 10, 0);

    for (auto ind : data)
    {
        // if (ind < cols.size())
        //     cols[ind]++;
        std::cout << ind << '\n';
    }

    // for (int i = 0; i < cols.size(); i++)
    // {
    //     std::cout << i + 1 << ": " << cols[i] << '\n';
    // }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int mod = std::atoi(argv[1]);

    collisions("../../postnummer.csv", mod);

    return 0;
}
