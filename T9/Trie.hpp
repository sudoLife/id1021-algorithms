#if !defined(TRIE_HPP)
#define TRIE_HPP

#include "Char.hpp"
#include <array>
#include <cassert>
#include <queue>

#define ALPHABET_LEN 27

struct Trie
{
    struct Node
    {
        bool word = false;
        Node *next = nullptr; // array of 27

        bool hasNext()
        {
            return next != nullptr;
        }
    };

    Trie()
    {
        root = new Node[ALPHABET_LEN];
    }

    Node *root = nullptr;

    void addWord(std::queue<Char> word)
    {
        addWordR(root, word);
    }

    std::vector<std::string> search(std::string path, Node *cur = nullptr)
    {
        if (path.empty())
        {
            return std::vector<std::string>();
        }
        std::string remainingPath = path.substr(1);

        if (cur == nullptr)
            cur = root;

        assert(path[0] > '0' && path[0] <= '9');
        int curIndex = path[0] - '1'; // gives us 0-8
        int curCode = curIndex * 3;

        std::vector<std::string> totalResult;

        for (int i = 0; i < 3; i++)
        {
            Node node = cur[curCode + i];

            if (node.word)
            {
                std::vector<std::string> branchResult;
                std::string curChar = Char::getChar(curCode + i).character;

                if (remainingPath.empty())
                {
                    branchResult.push_back(curChar);
                }
                else if (node.hasNext())
                {
                    auto childrenResults = search(remainingPath, node.next);

                    for (const std::string &res : childrenResults)
                    {
                        // assembling partial words & passing them up the line
                        if (res.length() >= remainingPath.length())
                            branchResult.push_back(curChar + res);
                    }
                }
                // concatenating results
                totalResult.insert(totalResult.end(), branchResult.begin(), branchResult.end());
            }
        }
        return totalResult;
    }
    // for every returned vector we prepend what we currently hold and return the result (?)

    ~Trie()
    {
        cleanup(root);
    }

private:
    void addWordR(Node *&cur, std::queue<Char> word)
    {
        if (word.empty()) // no more letters
            return;
        if (cur == nullptr)
            cur = new Node[ALPHABET_LEN];

        Char letter = word.front();
        int code = letter.code();
        word.pop();
        cur[code].word = true;
        addWordR(cur[letter.code()].next, word);
    }

    /**
     * @brief recursive cleanup
     * recursively deletes all allocated nodes
     * @param node
     */
    void cleanup(Node *&node)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < ALPHABET_LEN; i++)
        {
            Node *cur = &node[i];
            if (cur->next != nullptr)
            {
                cleanup(cur->next);
            }
        }

        delete[] node;
    }
};

#endif // TRIE_HPP
