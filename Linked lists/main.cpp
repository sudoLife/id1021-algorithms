#include "Node.hpp"
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

class AppendableArray
{
public:
    AppendableArray(std::size_t size)
    {
        arr = new int[size];

        // I know there's just going to be garbage in the first [size] elements
        // But do we care? no
        curSize = size;
    }

    void push(int n)
    {
        int *tmp = new int[curSize + 1];
        std::memcpy(tmp, arr, curSize * sizeof(int));

        curSize++;
        delete[] arr;
        arr = tmp;
    }

    void append(int n[], std::size_t size)
    {
        int *tmp = new int[curSize + size];
        std::memcpy(tmp, arr, curSize * sizeof(int));
        std::memcpy(tmp + curSize, n, size * sizeof(int));

        curSize += size;
        delete[] arr;
        arr = tmp;
    }

    ~AppendableArray()
    {
        delete[] arr;
    }

private:
    int *arr = nullptr;
    std::size_t curSize;
};

void checkAppend(int N)
{
    hclock::time_point t1, t2;
    int64_t node_dt, arr_dt;

    t1 = hclock::now();

    auto *node = new Node;
    node->value = -1;
    Node *head = nullptr;
    for (int size = 1; size < N; size++)
    {
        head = node->push(size, head);
    }
    t2 = hclock::now();

    node_dt = duration_cast<us>(t2 - t1).count();

    t1 = hclock::now();
    auto *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = i;
    }

    t2 = hclock::now();

    arr_dt = duration_cast<us>(t2 - t1).count();

    std::cout << N << " " << node_dt << " " << arr_dt << '\n';

    Node::clear(node);
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <N>\n";
        return 1;
    }

    int N2 = std::atoi(argv[1]);

    checkAppend(N2);
    return 0;

    int N1 = 1000;

    auto *first = new Node;
    auto *second = new Node;

    srand(time(NULL));

    // first.value = rand() & N1;
    first->value = 0;
    // fill the first node;
    Node *cachedHead = nullptr;

    for (int i = 1; i < N1; i++)
    {
        // first->push(rand() % N1);
        cachedHead = first->push(i, cachedHead);
    }

    second->value = 's';
    cachedHead = nullptr;

    for (int i = 1; i < N2; i++)
    {
        // second->push(rand() % N2);
        cachedHead = second->push(i, cachedHead);
    }

    AppendableArray arr(N1);
    int *arr2 = new int[N2];

    // first->print();

    hclock::time_point t1, t2;

    t1 = hclock::now();
    first->append(second);
    t2 = hclock::now();

    auto dt_node = duration_cast<us>(t2 - t1).count();

    t1 = hclock::now();
    arr.append(arr2, N2);
    t2 = hclock::now();

    auto dt_arr = duration_cast<us>(t2 - t1).count();

    std::cout << N2 << " " << dt_node << " " << dt_arr << '\n';

    // // We're done with this
    Node::clear(first);

    delete[] arr2;

    // NOTE: you cannot clear the second node, because it has already been cleared.

    return 0;
}
