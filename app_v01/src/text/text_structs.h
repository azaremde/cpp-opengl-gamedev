#pragma once

#include <glm/glm.hpp>

namespace text
{
    struct Character
    {
        unsigned int textureID;
        glm::vec2 size;
        glm::vec2 bearing;
        unsigned int advance;
    };
}