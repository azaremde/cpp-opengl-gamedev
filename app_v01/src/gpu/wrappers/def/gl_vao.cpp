#include "gpu/wrappers/gl_vao.h"

#include <gl/glew.h>

namespace gpu {
namespace wrap {

void GLvao::create_attribute(const unsigned int& attribute, const std::vector<float>& data, const unsigned int& size)
{
    GLvbo* vbo = new GLvbo(GL_ARRAY_BUFFER);

    vbo->bind();
    vbo->store_data(data);

    glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, size * 4, 0);

    vbo->unbind();

    vbos.push_back(vbo);

    attributes.push_back(attribute);
}

void GLvao::create_attribute(const unsigned int& attribute, const std::vector<int>& data, const unsigned int& size)
{
    GLvbo* vbo = new GLvbo(GL_ARRAY_BUFFER);

    vbo->bind();
    vbo->store_data(data);

    glVertexAttribIPointer(attribute, size, GL_INT, size * 4, 0);

    vbo->unbind();

    vbos.push_back(vbo);

    attributes.push_back(attribute);
}

void GLvao::create_index_buffer(const std::vector<int>& data)
{
    GLvbo* vbo = new GLvbo(GL_ELEMENT_ARRAY_BUFFER);

    vbo->bind();
    vbo->store_data(data);

    vertexCount = data.size();

    vbos.push_back(vbo);
}

void GLvao::create_index_buffer(const std::vector<unsigned int>& data)
{
    GLvbo* vbo = new GLvbo(GL_ELEMENT_ARRAY_BUFFER);

    vbo->bind();
    vbo->store_data(data);

    vertexCount = data.size();

    vbos.push_back(vbo);
}

}
}