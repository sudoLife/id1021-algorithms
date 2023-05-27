#include <iostream>

int main()
{
    std::string testStr = "öäÅ";

    for (int i = 0; i < testStr.length(); i += 2)
    {
        int value = 0;
        value += testStr[i] << 8;
        value += testStr[i + 1];

        std::cout << testStr[i] << testStr[i + 1] << " = " << value << '\n';
    }

    return 0;
}