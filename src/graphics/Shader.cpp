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
    try {
        dispose();
    } catch (Exception& e) {
        LOG_CRITICAL("Could not free resources of shader. GPU memory leak");
    }
}

// public:

void Shader::load(const std::string& vertPath, const std::string& fragPath)
{
    try {
        if (m_loaded) {
            LOG_WARN("Shader is already loaded. Deleting previous data");
            dispose();
        }

        m_vertPath = vertPath;
        m_fragPath = fragPath;
        m_shaderProgram = build(vertPath, fragPath);
        LOG_INFO("Loaded Shader \"{}, {}\"", m_vertPath, m_fragPath);

    } catch (Exception& e) {
        LOG_ERROR("Could not load Shader: {}", e.what());
        throw Exception("Failed to load Shader");
    }
}

void Shader::dispose()
{
    try {
        if (!m_loaded)
            return;

        deleteProgram(m_shaderProgram);

        m_vertPath.clear();
        m_fragPath.clear();
        m_loaded = false;

    } catch (Exception& e) {
        LOG_ERROR("Failed to dispose of Shader");
        throw Exception("Failed to dispose of Shader");
    }
}

void Shader::reload()
{
    try {
        GLuint tempSha = build(m_vertPath, m_fragPath);

        disable();  // Just to force the user to re-enable the shader
        deleteProgram(m_shaderProgram);
        m_uniformCache.clear();
        m_shaderProgram = tempSha;

        LOG_DEBUG("Reloaded shader \"{}, {}\"...", m_vertPath, m_fragPath);

    } catch (Exception& e) {
        LOG_ERROR("Could not reload Shader: {}", e.what());
        throw Exception("Failed to reload Shader");
    }
}

void Shader::setUniform1i(const std::string& uniformName, int i)
{
    try {
        enable();
        glCheck(glUniform1i(getUniformLocation(uniformName), i));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform 1i: {}", e.what());
        throw Exception("Failed to set uniform 1i");
    }
}

void Shader::setUniform1f(const std::string& uniformName, float f)
{
    try {
        enable();
        glCheck(glUniform1f(getUniformLocation(uniformName), f));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform 1f: {}", e.what());
        throw Exception("Failed to set uniform 1f");
    }
}

void Shader::setUniform2f(const std::string& uniformName, float x, float y)
{
    try {
        enable();
        glCheck(glUniform2f(getUniformLocation(uniformName), x, y));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform 2f: {}", e.what());
        throw Exception("Failed to set uniform 2f");
    }
}

void Shader::setUniform3f(const std::string& uniformName, float x, float y, float z)
{
    try {
        enable();
        glCheck(glUniform3f(getUniformLocation(uniformName), x, y, z));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform 3f: {}", e.what());
        throw Exception("Failed to set uniform 3f");
    }
}

void Shader::setUniform4f(const std::string& uniformName, float x, float y, float z, float w)
{
    try {
        enable();
        glCheck(glUniform4f(getUniformLocation(uniformName), x, y, z, w));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform 4f: {}", e.what());
        throw Exception("Failed to set uniform 4f");
    }
}

void Shader::setUniformMatrix4fv(const std::string& uniformName, const Matrix4f& transform)
{
    try {
        enable();
        glCheck(glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, maths::matrix::value_ptr(transform)));

    } catch (Exception& e) {
        LOG_ERROR("Could not set uniform matrix 4fv: {}", e.what());
        throw Exception("Failed to set uniform matrix 4fv");
    }
}

// private:

GLuint Shader::build(const std::string& vertPath, const std::string& fragPath) const
{
    try {
        GLuint vertSha = createShader(vertPath, GL_VERTEX_SHADER);
        GLuint fragSha = createShader(fragPath, GL_FRAGMENT_SHADER);

        GLuint sha = createProgram(vertSha, fragSha);

        deleteShader(vertSha);
        deleteShader(fragSha);

        return sha;

    } catch (Exception& e) {
        LOG_ERROR("Could not build Shader: {}", e.what());
        throw Exception("Failed to build Shader");
    }
}

GLuint Shader::createShader(const std::string& filePath, GLenum shaderType) const
{
    try {
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

    } catch (Exception& e) {
        LOG_ERROR("Could not create Shader: {}", e.what());
        throw Exception("Failed to create Shader");
    }
}

GLuint Shader::createProgram(GLuint vertexShaderID, GLuint fragmentShaderID) const
{
    try {
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

    } catch (Exception& e) {
        LOG_ERROR("Could not create shader program: {}");
        throw Exception("Failed to create shader program");
    }
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
    try {
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

    } catch (Exception& e) {
        LOG_ERROR("Could not get uniform location: {}", e.what());
        throw Exception("Failed to get uniform location");
    }
}

}  // namespace tk
