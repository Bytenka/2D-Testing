#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

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

    WindowUID createWindow(unsigned width, unsigned height, const std::string &title);

  private:
    Application();
    ~Application();

  public:
    Application(const Application &) = delete;
    void operator=(const Application &) = delete;
};

// callbacks:

void glfw_error_callback(int error_code, const char *description);
} // namespace tk

// Singleton pattern from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289