#pragma once

#include "Camera.h"

#include <memory>

namespace tk {
class Window;
class Shader;

class Renderer
{
  public:
    Renderer(const Window* attachedWindow);
    ~Renderer();

    void init();
    void dispose();

    void drawNewFrame();

  private:
  private:
    const Window* m_attachedWindow;

    Camera m_mainCamera;
    std::shared_ptr<Shader> m_mainShader;
    bool m_initialized = false;
};

}  // namespace tk