#include <queue>
#include <string>

struct Char
{
    Char(const std::string &ch) : character(ch) {}

    int code()
    {
        // Plain ascii
        if (character.length() == 1)
        {
            char chr = character[0];
            // a - p
            if (chr <= 'p')
            {
                return chr - 'a';
            }
            // r - v
            if (chr >= 'r' && chr <= 'v')
            {
                return chr - 'a' - 1;
            }
            // x - z
            if (chr >= 'x' && chr <= 'z')
            {
                return chr - 'a' - 2;
            }
        }

        // Swedish
        switch (character[1])
        {
        case -91: // bubble a
            return 24;
        case -92: // dotted a
            return 25;
        case -74: // dotted o
            return 26;
        }

        throw std::runtime_error("Unknown character");
    }

    // returns a vector of characters
    static std::queue<Char> parse(const std::string &str)
    {
        std::queue<Char> parsed;

        for (int i = 0; i < str.length(); i++)
        {
            std::string chr;
            chr += str[i];

            // swedish character
            if (str[i] < 0)
            {
                chr += str[i + 1];
                i++;
            }
            parsed.emplace(chr);
        }

        return parsed;
    }

    int key()
    {
        return code() / 3 + 1;
    }

    static int key(Char chr)
    {
        return chr.code() / 3 + 1;
    }

    static int key2index(int key)
    {
        return key - 1;
    }

    static Char getChar(int code)
    {
        if (code < 0 || code > 26)
            throw std::runtime_error("Index out of bounds");

        std::string chr;

        if (code <= 15) // a - p
        {
            chr += char('a' + code);
            return Char(chr);
        }

        if (code <= 20) // r - v
        {
            chr += char('a' + code + 1);
            return Char(chr);
        }

        if (code <= 23)
        {
            chr += char('a' + code + 2);
            return Char(chr);
        }

        // double characters
        chr += char(-61);
        switch (code)
        {
        case 24:
            chr += char(-91);
            break;
        case 25:
            chr += char(-92);
            break;
        case 26:
            chr += char(-74);
            break;
        }

        return Char(chr);
    }

    std::string character;
};