#pragma once

#include <string>
#include <vector>
#include <map>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl/glew.h>
#include <spdlog/spdlog.h>

#include "math/math.h"

namespace gpu {
namespace wrap {

using str_list = std::vector<std::string>;

class GLShader
{
protected:
    unsigned int programID;

    GLShader(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath,
        std::vector<std::string> uniformVariables,
        std::vector<std::string> inputVariables
    );

private:
    std::map<std::string, int> locations;
    unsigned int location;

    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    void link() const;
    unsigned int createShader(const std::string& shaderCode, const unsigned int& shaderType);

public:
    inline unsigned int getProgramID() const
    {
        return programID;
    }

    inline void bind() const
    {
        glUseProgram(programID);
    }

    inline void unbind() const
    {
        glUseProgram(0);
    }

    inline void cleanUp()
    {
        if (programID != 0)
        {
            glDetachShader(programID, vertexShaderID);
            glDetachShader(programID, fragmentShaderID);
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
            glDeleteProgram(programID);
        }
    }      

    inline void createUniform(const std::string& name)
    {
        const int location = glGetUniformLocation(programID, name.c_str());

        locations.insert(std::pair<std::string, int>(name.c_str(), location));
    }

    inline void set_mat4x4(const std::string& name, const math::mat4x4& matrix)
    {
        #if defined _DEBUG || defined ENGINE_DEBUG_MODE
        if (locations.find(name) == locations.end())
        {
            spdlog::error("[DEBUG][gl_shader.h]: Variable {0} doesn't exist.", name);
            return;
        }        
        #endif

        location = locations.at(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    inline void set_mat4x4(const std::string& name, const glm::mat4x4& matrix)
    {
        #if defined _DEBUG || defined ENGINE_DEBUG_MODE
        if (locations.find(name) == locations.end())
        {
            spdlog::error("[DEBUG][gl_shader.h]: Variable {0} doesn't exist.", name);
            return;
        }        
        #endif

        location = locations.at(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    inline GLShader& operator[](std::string const& name)
    {
        location = locations.at(name);
        return *this;
    }

    inline void operator=(const glm::mat4x4& matrix) const
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    inline void operator=(float r[4][4]) const
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &r[0][0]);
    }

    inline void operator=(const glm::mat4x4* matrix) const
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &(*matrix)[0][0]);
    }

    inline void operator=(const std::vector<glm::mat4x4>& list) const
    {
        for (unsigned int i = 0; i < list.size(); i++)
        {
            glUniformMatrix4fv(location, list.size(), GL_FALSE, glm::value_ptr(list[0]));
        }
    }

    inline void operator=(const std::vector<glm::mat4x4>* list) const
    {
        for (unsigned int i = 0; i < list->size(); i++)
        {
            glUniformMatrix4fv(location, list->size(), GL_FALSE, glm::value_ptr((*list)[0]));
        }
    }

    inline void operator=(const glm::vec3& vec) const
    {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    inline void operator=(const glm::vec4& vec) const
    {
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }

    inline void operator=(float* value) const
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }

    inline void operator=(float value) const
    {
        glUniform1f(location, value);
    }

    inline void operator=(bool value) const
    {
        glUniform1i(location, value ? 1 : 0);
    }
};

}
}