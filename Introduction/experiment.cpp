#include <iostream>
#include <vector>


int main()
{
    std::vector<int> test({1, 2, 3, 4, 5, 7, 8, 9});
    std::vector<int> test2({1, 2, 3, 4, 5, 7, 8, 9});

    for (const auto &el : test)
    {
        printf("%d\n", el);
    }

    return 0;
}
