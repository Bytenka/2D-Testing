#include "pch.h"

#include "Shader.h"

#include <system/Log.h>
#include <system/exception/Exception.h>
#include <system/exception/InvalidArgumentException.h>
#include <system/utils.h>

namespace tk {

Shader::Shader()
{
}

Shader::~Shader()
{
    if (m_loaded)
        LOG_CRITICAL("Shader destructor called but resources were not freed. GPU memory leak");
}

// public:

void Shader::load(const std::string& vertPath, const std::string& fragPath)
{
    if (m_loaded)
        dispose();

    m_vertPath = vertPath;
    m_fragPath = fragPath;
    m_shaderProgram = build(vertPath, fragPath);
    LOG_INFO("Loaded shader \"{}, {}\"", m_vertPath, m_fragPath);
}

void Shader::dispose()
{
    if (!m_loaded)
        return;

    deleteProgram(m_shaderProgram);

    m_vertPath.clear();
    m_fragPath.clear();
    m_loaded = false;
}

void Shader::reload()
{
    GLuint tempSha = build(m_vertPath, m_fragPath);

    disable();  // Just to force the user to re-enable the shader
    deleteProgram(m_shaderProgram);
    m_uniformCache.clear();
    m_shaderProgram = tempSha;

    LOG_DEBUG("Reloaded shader \"{}, {}\"...", m_vertPath, m_fragPath);
}

void Shader::setUniform1i(const std::string& uniformName, int i)
{
    enable();
    glCheck(glUniform1i(getUniformLocation(uniformName), i));
}

void Shader::setUniform1f(const std::string& uniformName, float f)
{
    enable();
    glCheck(glUniform1f(getUniformLocation(uniformName), f));
}

void Shader::setUniform2f(const std::string& uniformName, float x, float y)
{
    enable();
    glCheck(glUniform2f(getUniformLocation(uniformName), x, y));
}

void Shader::setUniform3f(const std::string& uniformName, float x, float y, float z)
{
    enable();
    glCheck(glUniform3f(getUniformLocation(uniformName), x, y, z));
}

void Shader::setUniform4f(const std::string& uniformName, float x, float y, float z, float w)
{
    enable();
    glCheck(glUniform4f(getUniformLocation(uniformName), x, y, z, w));
}

void Shader::setUniformMatrix4fv(const std::string& uniformName, const Matrix4f& transform)
{
    enable();
    glCheck(glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, maths::matrix::value_ptr(transform)));
}

// private:

GLuint Shader::build(const std::string& vertPath, const std::string& fragPath) const
{
    GLuint vertSha = createShader(vertPath, GL_VERTEX_SHADER);
    GLuint fragSha = createShader(fragPath, GL_FRAGMENT_SHADER);

    GLuint sha = createProgram(vertSha, fragSha);

    deleteShader(vertSha);
    deleteShader(fragSha);

    return sha;
}

GLuint Shader::createShader(const std::string& filePath, GLenum shaderType) const
{
    if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER)
        throw InvalidArgumentException("Shader type invalid or unsupported");

    std::string shaSourceStr(read_file(filePath.c_str()));
    const char* shaSource = shaSourceStr.c_str();

    GLuint sha;
    glCheck(sha = glCreateShader(shaderType));  // Errors will be caught below
    if (sha == 0)
        throw Exception("OpenGL call to create shader failed. Is context valid?");

    glCheck(glShaderSource(sha, 1, &shaSource, NULL));
    glCheck(glCompileShader(sha));

    // Error checking
    int success;
    glCheck(glGetShaderiv(sha, GL_COMPILE_STATUS, &success));  // Errors will be caught below
    if (!success) {
        char infoLog[512];
        glCheck(glGetShaderInfoLog(sha, 512, NULL, infoLog));
        throw Exception("Compilation error: " + std::string(infoLog));
    }

    return sha;
}

GLuint Shader::createProgram(GLuint vertexShaderID, GLuint fragmentShaderID) const
{
    GLuint prog;
    glCheck(prog = glCreateProgram());
    if (prog == 0)
        throw Exception("OpenGL call to create program shader failed. Is context valid?");

    glCheck(glAttachShader(prog, vertexShaderID));
    glCheck(glAttachShader(prog, fragmentShaderID));
    glCheck(glLinkProgram(prog));

    // Error checking
    int success;
    glCheck(glGetProgramiv(prog, GL_LINK_STATUS, &success));
    if (!success) {
        char infoLog[512];
        glCheck(glGetProgramInfoLog(prog, 512, NULL, infoLog));
        throw Exception("Linking error: " + std::string(infoLog));
    }

    // Detach so they can be effectively deleted after that (cf doc)
    glCheck(glDetachShader(prog, vertexShaderID));
    glCheck(glDetachShader(prog, fragmentShaderID));

    return prog;
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
    auto it = std::find_if(
        m_uniformCache.begin(),
        m_uniformCache.end(),
        [&](const std::pair<std::string, GLuint>& current) {
            return (current.first) == uniformName;
        });

    if (it != m_uniformCache.end())
        return it->second;

    // If not in cache, add it
    GLint newValue;
    glCheck(newValue = glGetUniformLocation(m_shaderProgram, uniformName.c_str()));

    if (newValue == -1)
        throw InvalidArgumentException("Uniform \"" + uniformName + "\" does not exist or is invalid");

    m_uniformCache.push_back(std::make_pair(uniformName, newValue));

    return newValue;
}

}  // namespace tk
