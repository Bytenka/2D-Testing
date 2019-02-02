#pragma once

#include <graphics/Shader.h>

#include <string>
#include <unordered_map>
#include <memory>

namespace tk {
class ShaderManager
{
  public:
    static std::shared_ptr<Shader> getShader(const std::string& shaderPairName);

  private:
    inline static ShaderManager& getInstance()
    {
        static ShaderManager instance;
        return instance;
    }
    void loadShader(const std::string& shaderPairName);

    ShaderManager();
    ~ShaderManager();

  private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::string m_shaderFolderPath;

  public:
    ShaderManager(const ShaderManager&) = delete;
    void operator=(const ShaderManager&) = delete;
};
}  // namespace tk