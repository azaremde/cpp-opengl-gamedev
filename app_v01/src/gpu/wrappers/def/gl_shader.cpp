#include "gpu/wrappers/gl_shader.h"

#include <gl/glew.h>

#include "assets/asset.h"

#include <spdlog/spdlog.h>

namespace gpu {
namespace wrap {

GLShader::GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::vector<std::string> uniformVariables, std::vector<std::string> inputVariables)
{
    assets::Text vs_shader;
    assets::Text fs_shader;
    assets::load(&vs_shader, vertexShaderPath);
    assets::load(&fs_shader, fragmentShaderPath);

    programID = glCreateProgram();

    vertexShaderID = createShader(vs_shader.content, GL_VERTEX_SHADER);
    fragmentShaderID = createShader(fs_shader.content, GL_FRAGMENT_SHADER);

    link();

    for (int i = 0; i < uniformVariables.size(); i++)
    {
        createUniform(uniformVariables[i]);
    }

    for (int i = 0; i < inputVariables.size(); i++)
    {
        glBindAttribLocation(programID, i, inputVariables[i].c_str());
    }
}

void GLShader::link() const
{
    glLinkProgram(programID);

    if (vertexShaderID != 0)
    {
        glDetachShader(programID, vertexShaderID);
    }

    if (fragmentShaderID != 0)
    {
        glDetachShader(programID, fragmentShaderID);
    }

    glValidateProgram(programID);
}

unsigned int GLShader::createShader(const std::string& shaderCode, const unsigned int& shaderType)
{
    const unsigned int shaderID = glCreateShader(shaderType);

    const char* c_str = shaderCode.c_str();

    glShaderSource(shaderID, 1, &c_str, NULL);
    glCompileShader(shaderID);

    int status;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetShaderInfoLog(shaderID, length, &length, &log[0]);
        spdlog::error("Error occured while compiling a shader: {0}", &log[0]);
        return -1;
    }

    glAttachShader(programID, shaderID);

    return shaderID;
}

}
}