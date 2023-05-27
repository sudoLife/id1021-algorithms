#include <iostream>

int main()
{
    std::string swedes("åäö");

    for (int i = 0; i < swedes.length(); i++)
    {
        std::cout << int(swedes[i]) << '\n';
    }

    return 0;
}