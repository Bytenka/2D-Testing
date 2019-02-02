#include "pch.h"
#include "ShaderManager.h"

#include <system/Log.h>
#include <system/exception/Exception.h>

namespace tk {
ShaderManager::ShaderManager()
    : m_shaderFolderPath("res/shaders")
{
}

ShaderManager::~ShaderManager()
{
    for (auto& i : m_shaders) {
        if (i.second.use_count() > 1)
            LOG_WARN("Deleting shader \"{}\" from manager, but it is still used somewere", i.first);
    }
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& shaderPairName)
{
    try {
        ShaderManager& shaderManager = ShaderManager::getInstance();

        auto shader = shaderManager.m_shaders.find(shaderPairName);

        if (shader == shaderManager.m_shaders.end()) {
            shaderManager.loadShader(shaderPairName);
            return shaderManager.m_shaders[shaderPairName];
        } else
            return shader->second;

    } catch (Exception& e) {
        LOG_ERROR("Could not get Shader: {}", e.what());
        throw Exception("Failed to get Shader");
    }
}

// public:

// private:

void ShaderManager::loadShader(const std::string& shaderPairName)
{
    try {
        std::string shaderPath = m_shaderFolderPath + "/" + shaderPairName;

        auto pair = std::make_pair(shaderPairName, std::make_shared<Shader>());
        pair.second->load(shaderPath + ".vert", shaderPath + ".frag");
        m_shaders.insert(std::move(pair));

    } catch (Exception& e) {
        LOG_ERROR("Could not load Shader \"{}\": {}", shaderPairName, e.what());
        throw Exception("Failed to load Shader");
    }
}
}  // namespace tk