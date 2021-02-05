#pragma once

#include <vector>
#include <GL/glew.h>

namespace gpu {
namespace wrap {

class GLvbo
{
private:
    unsigned int id;
    unsigned int type;

public:
    inline GLvbo(const unsigned int& type)
    {
        glGenBuffers(1, &id);

        this->type = type;
    }

    inline ~GLvbo()
    {
    }

    inline void store_data(const std::vector<float>& data) const
    {
        glBufferData(type, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    }

    inline void store_data(const std::vector<int>& data) const
    {
        glBufferData(type, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
    }

    inline void store_data(const std::vector<unsigned int>& data) const
    {
        glBufferData(type, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
    }

    inline void bind() const
    {
        glBindBuffer(type, id);
    }

    inline void unbind() const
    {
        glBindBuffer(type, 0);
    }
};

}
}
