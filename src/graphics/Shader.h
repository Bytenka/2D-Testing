#pragma once

#include "GLCheck.h"
#include <glad/glad.h>
#include <maths/Maths.h>

#include <string>
#include <vector>
#include <utility>

namespace tk {
class Shader
{
  public:
    Shader();
    ~Shader();

    inline void enable() const { glCheck(glUseProgram(m_shaderProgram)); }
    inline void disable() const { glCheck(glUseProgram(0)); }

    void load(const std::string& vertPath, const std::string& fragPath);
    void dispose();
    void reload();  // Shader need to be re-enabled after calling this function

    void setUniform1i(const std::string& uniformName, int i);
    void setUniform1f(const std::string& uniformName, float f);
    void setUniform2f(const std::string& uniformName, float x, float y);
    void setUniform3f(const std::string& uniformName, float x, float y, float z);
    void setUniform4f(const std::string& uniformName, float x, float y, float z, float w);
    void setUniformMatrix4fv(const std::string& uniformName, const Matrix4f& transform);

  private:
    GLuint build(const std::string& vertPath, const std::string& fragPath) const;
    GLuint createShader(const std::string& filePath, GLenum shaderType) const;
    GLuint createProgram(GLuint vertexShaderID, GLuint fragmentShaderID) const;
    inline void deleteShader(GLuint shaderID) const { glCheck(glDeleteShader(shaderID)); }
    inline void deleteProgram(GLuint programID) const { glCheck(glDeleteProgram(m_shaderProgram)); }

    GLint getUniformLocation(const std::string& uniformName);

  private:
    std::string m_vertPath;
    std::string m_fragPath;

    bool m_loaded = false;
    GLuint m_vertexShader = 0, m_fragmentShader = 0, m_shaderProgram = 0;
    std::vector<std::pair<std::string, GLint>> m_uniformCache;

  public:
    Shader(const Shader&) = delete;
    void operator=(const Shader&) = delete;
};

}  // namespace tk
