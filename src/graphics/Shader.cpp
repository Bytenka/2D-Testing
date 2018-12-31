#include "pch.h"
#include "Shader.h"

#include <system/exception/Exception.h>
#include <system/Log.h>
#include <system/utils.h>

#include <glm/gtc/type_ptr.hpp>

namespace tk
{

Shader::Shader()
{
}

Shader::~Shader()
{
    deleteProgram();
}

// public:

void Shader::reload()
{
    LOG_DEBUG("Reloading shader \"{}, {}\"...", m_vertPath, m_fragPath);
    deleteProgram();
    load(m_vertPath, m_fragPath);
}

void Shader::setUniform1i(const std::string &uniformName, int i)
{
    enable();
    glCheck(glUniform1i(getUniformLocation(uniformName), i));
}

void Shader::setUniform1f(const std::string &uniformName, float f)
{
    enable();
    glCheck(glUniform1f(getUniformLocation(uniformName), f));
}

void Shader::setUniform2f(const std::string &uniformName, float x, float y)
{
    enable();
    glCheck(glUniform2f(getUniformLocation(uniformName), x, y));
}

void Shader::setUniform3f(const std::string &uniformName, float x, float y, float z)
{
    enable();
    glCheck(glUniform3f(getUniformLocation(uniformName), x, y, z));
}

void Shader::setUniform4f(const std::string &uniformName, float x, float y, float z, float w)
{
    enable();
    glCheck(glUniform4f(getUniformLocation(uniformName), x, y, z, w));
}

void Shader::setUniformMatrix4fv(const std::string &uniformName, const glm::mat4 &transform)
{
    enable();
    glCheck(glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(transform)));
}

// private:

void Shader::load(const std::string &vertPath, const std::string &fragPath)
{
    std::string prevVert = m_vertPath;
    std::string prevFrag = m_fragPath;
    try
    {
        m_vertPath = vertPath;
        m_fragPath = fragPath;

        createShader(GL_VERTEX_SHADER);
        createShader(GL_FRAGMENT_SHADER);

        createProgram();

        deleteShader(GL_VERTEX_SHADER);
        deleteShader(GL_FRAGMENT_SHADER);

        LOG_INFO("Loaded shader \"{}, {}\"", m_vertPath, m_fragPath);
    }
    catch (Exception &e)
    {
        m_vertPath = prevVert;
        m_fragPath = prevFrag;
        LOG_ERROR("Could not create shader: {}", e.what());
    }
}

void Shader::createShader(GLenum shaderType)
{
    GLuint *toModify = nullptr;
    std::string *toModifyPath = nullptr;
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        toModify = &m_vertexShader;
        toModifyPath = &m_vertPath;
        break;
    case GL_FRAGMENT_SHADER:
        toModify = &m_fragmentShader;
        toModifyPath = &m_fragPath;
        break;
    default:
        throw std::invalid_argument("Shader type unsupported or incorrect");
        break;
    }

    std::string shaSourceStr(read_file(toModifyPath->c_str()));
    const char *shaSource = shaSourceStr.c_str();

    GLuint sha;
    glCheck(sha = glCreateShader(shaderType)); // Errors will be caught below
    if (sha == 0)
        throw Exception("OpenGL call to create shader failed. Is context valid?");

    glCheck(glShaderSource(sha, 1, &shaSource, NULL));
    glCheck(glCompileShader(sha));

    // Error checking
    int success;
    glCheck(glGetShaderiv(sha, GL_COMPILE_STATUS, &success)); // Errors will be caught below
    if (!success)
    {
        char infoLog[512];
        glCheck(glGetShaderInfoLog(sha, 512, NULL, infoLog));
        throw Exception("Compilation error: " + std::string(infoLog));
    }

    *toModify = sha;
}

void Shader::deleteShader(GLenum shaderType)
{
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        if (m_vertexShader != 0)
            glCheck(glDeleteShader(m_vertexShader));

        m_vertexShader = 0;
        break;
    case GL_FRAGMENT_SHADER:
        if (m_fragmentShader != 0)
            glCheck(glDeleteShader(m_fragmentShader));

        m_fragmentShader = 0;
        break;
    default:
        throw std::invalid_argument("Shader type unsupported or incorrect");
        break;
    }
}

void Shader::createProgram()
{
    GLuint prog;
    glCheck(prog = glCreateProgram());
    if (prog == 0)
        throw Exception("OpenGL call to create program shader failed. Is context valid?");

    glCheck(glAttachShader(prog, m_vertexShader));
    glCheck(glAttachShader(prog, m_fragmentShader));
    glCheck(glLinkProgram(prog));

    // Error checking
    int success;
    glCheck(glGetProgramiv(prog, GL_LINK_STATUS, &success));
    if (!success)
    {
        char infoLog[512];
        glCheck(glGetProgramInfoLog(prog, 512, NULL, infoLog));
        throw Exception("Linking error: " + std::string(infoLog));
    }

    // Detach so they can actually be deleted after that
    glCheck(glDetachShader(prog, m_vertexShader));
    glCheck(glDetachShader(prog, m_fragmentShader));

    m_shaderProgram = prog;
}

void Shader::deleteProgram() noexcept
{
    if (m_shaderProgram != 0)
        glCheck(glDeleteProgram(m_shaderProgram));

    m_uniformCache.clear();
}

GLint Shader::getUniformLocation(const std::string &uniformName)
{
    auto it = std::find_if(
        m_uniformCache.begin(),
        m_uniformCache.end(),
        [&](const std::pair<std::string, GLuint> &current) {
            return (current.first) == uniformName;
        });

    if (it != m_uniformCache.end())
        return it->second;

    // If not in cache, add it
    GLint newValue;
    glCheck(newValue = glGetUniformLocation(m_shaderProgram, uniformName.c_str()));

    if (newValue == -1)
        throw std::invalid_argument("Uniform \"" + uniformName + "\" does not exist or is invalid");

    m_uniformCache.push_back(std::make_pair(uniformName, newValue));

    return newValue;
}

} // namespace tk
