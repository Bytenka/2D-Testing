#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Renderer.h>
#include <maths/Maths.h>

#include <string>

namespace tk {

class Window
{
  public:
    Window(unsigned width, unsigned height, const std::string& title);
    ~Window();

    void update() noexcept;
    void setClearColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) const noexcept;
    void setIcon(const std::string& imgPath) noexcept;
    void updateSize(int width, int height) noexcept;
    void useMouseAsInput(bool value) noexcept;
    void display();

    void clear() const;
    inline unsigned getWidth() const noexcept { return m_width; }
    inline unsigned getHeight() const noexcept { return m_height; }
    inline const std::string& getTitle() const noexcept { return m_title; }
    inline Vector2d getCursorTravel() const noexcept { return m_mouseIsInput ? m_cursorPos : Vector2d(0); }
    inline Vector2d getCursorPosition() const noexcept { return m_mouseIsInput ? Vector2d(0) : m_cursorPos; }
    inline GLFWwindow* getGLFWwindow() const noexcept { return m_glfwWindow; }
    inline bool shouldClose() const noexcept { return glfwWindowShouldClose(m_glfwWindow); }

  private:
    inline void bindContext() const noexcept
    {
        if (glfwGetCurrentContext() != m_glfwWindow)
            glfwMakeContextCurrent(m_glfwWindow);
    }
    inline void unbindContext() const noexcept
    {
        if (glfwGetCurrentContext() == m_glfwWindow)
            glfwMakeContextCurrent(NULL);
    }

  private:
    Renderer m_renderer;

    std::string m_title;
    unsigned m_width;
    unsigned m_height;
    Vector2d m_cursorPos;

    GLFWwindow* m_glfwWindow = NULL;
    bool m_mouseIsInput;

  public:
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;

  private:
    // callbacks:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;
};
}  // namespace tk