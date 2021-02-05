#pragma once

#include <vector>

#include "gl_vbo.h"

namespace gpu {
namespace wrap {

class GLvao
{
private:
    unsigned int id;
    unsigned int vertexCount;
    std::vector<GLvbo*> vbos;
    std::vector<unsigned int> attributes;

public:
    void create_attribute(const unsigned int& attribute, const std::vector<float>& data, const unsigned int& size);
    void create_attribute(const unsigned int& attribute, const std::vector<int>& data, const unsigned int& size);
    void create_index_buffer(const std::vector<int>& data);
    void create_index_buffer(const std::vector<unsigned int>& data);   

    inline GLvao()
    {
        glGenVertexArrays(1, &id);
        vertexCount = 0;
    }

    inline ~GLvao() { } 

    inline void bind() const
    {
        glBindVertexArray(id);

        for (int i = 0; i < attributes.size(); i++)
        {
            glEnableVertexAttribArray(attributes[i]);
        }
    }

    inline void unbind() const
    {
        glBindVertexArray(0);

        for (int i = 0; i < attributes.size(); i++)
        {
            glDisableVertexAttribArray(attributes[i]);
        }
    }

    inline unsigned int get_id() const
    {
        return id;
    }

    inline unsigned int get_vertex_count() const
    {
        return vertexCount;
    }
};

}
}
