#pragma once

#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <utility>
#include <memory>

#define WINDOW_NULL 0

namespace tk
{
typedef unsigned long long WindowUID;

class Application
{
public:
  inline static Application &getInstance()
  {
    static Application instance;
    return instance;
  }

  void runLoop();
  WindowUID createWindow(unsigned width, unsigned height, const std::string &title) noexcept;
  void destroyWindow(WindowUID uid) noexcept;

  Window *getInternalWindow(WindowUID uid) noexcept;

  inline void setMainWindow(WindowUID uid) noexcept { m_mainWindowUID = uid; }

private:
  Application();
  ~Application();

  std::vector<std::pair<WindowUID, std::unique_ptr<Window>>>::iterator getWindowFromUID(WindowUID uid);
  std::vector<std::pair<WindowUID, std::unique_ptr<Window>>>::iterator getWindowFromGLFWwindow(GLFWwindow *window);

private:
  std::vector<std::pair<WindowUID, std::unique_ptr<Window>>> m_windows;
  WindowUID m_mainWindowUID = WINDOW_NULL;
  WindowUID m_windowUIDCounter = 1;
  bool m_shouldTerminate = false;

public:
  Application(const Application &) = delete;
  void operator=(const Application &) = delete;

private:
  // callbacks:
  static void glfw_error_callback(int error_code, const char *description);
};
} // namespace tk

// Singleton pattern from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289