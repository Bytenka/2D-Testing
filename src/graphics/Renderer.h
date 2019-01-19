#pragma once

#include "Camera.h"
#include "Shader.h"

namespace tk {
class Window;

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

    Shader m_mainShader;
    Camera m_mainCamera;
    bool m_initialized = false;
};

}  // namespace tk