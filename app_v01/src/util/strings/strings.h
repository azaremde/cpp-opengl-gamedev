#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util {
namespace str {

inline std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter))
    {
        if (token.length() > 0)
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}
        
} // namespace str
} // namespace util