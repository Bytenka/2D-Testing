#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <graphics/GLCheck.h>

#include <string>

namespace tk
{
class Window
{
public:
  Window(unsigned width, unsigned height, const std::string &title);
  ~Window();

  void update() noexcept;
  void setClearColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) const noexcept;
  void setIcon(const std::string &imgPath);
  void updateSize(int width, int height) noexcept;
  void useMouseAsInput(bool value) noexcept;

  inline void bindContext() const noexcept { glfwMakeContextCurrent(m_glfwWindow); } // Should be called before anything else related to graphics
  inline void unbindContext() const noexcept { glfwMakeContextCurrent(NULL); }
  inline void clear() const { glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }
  inline void display() const noexcept { glfwSwapBuffers(m_glfwWindow); }
  inline unsigned getWidth() const noexcept { return m_width; }
  inline unsigned getHeight() const noexcept { return m_height; }
  inline const std::string &getTitle() const noexcept { return m_title; }
  inline glm::dvec2 getCursorTravel() const noexcept { return m_mouseIsInput ? m_cursorTravel : glm::dvec2(0); }
  inline GLFWwindow *getGLFWwindow() const noexcept { return m_glfwWindow; }
  inline bool shouldClose() const noexcept { return glfwWindowShouldClose(m_glfwWindow); }

private:
  std::string m_title;
  unsigned m_width;
  unsigned m_height;
  glm::dvec2 m_cursorPos;

  GLFWwindow *m_glfwWindow = NULL;
  bool m_mouseIsInput;
  glm::dvec2 m_cursorTravel; // Distance moved by the cursor between calls of update()

public:
  Window(const Window &) = delete;
  void operator=(const Window &) = delete;
};

// callbacks:
void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept;
} // namespace tk