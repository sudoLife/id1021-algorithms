#include <fstream>
#include <iostream>
#include <vector>

#include "Trie.hpp"

int main()
{

    std::string filename{"../kelly.txt"};
    std::ifstream file(filename);
    std::string line;
    Trie trie;
    std::vector<std::string> encoded;
    while (std::getline(file, line))
    {
        auto parsed = Char::parse(line);
        trie.addWord(Char::parse(line));

        std::string sequence;
        while (!parsed.empty())
        {
            sequence += char(parsed.front().key() + '0');
            parsed.pop();
        }

        encoded.push_back(sequence);
    }
    for (auto sequence : encoded)
    {
        auto result = trie.search(sequence);
        for (const auto &str : result)
        {
            std::cout << str << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
