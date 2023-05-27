#include "DynamicQueue.hpp"
#include "Tree.hpp"
#include <chrono>
#include <vector>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

int main(int argc, char *argv[])
{
    DynamicQueue<int> queue(4);

    queue.print();

    return 0;
}
