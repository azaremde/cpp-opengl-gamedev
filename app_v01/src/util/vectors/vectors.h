#pragma once

#include <vector>

namespace util {
namespace vec {

template <typename T>
inline bool contains(const std::vector<T>& vector, const T& item)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] == item)
        {
            return true;
        }
    }

    return false;
}

} // namespace vec
} // namespace util