#include "Application.h"

#include <system/Log.h>
#include <system/exception/Exception.h>
#include <system/exception/GLFWException.h>

#include <iostream>

namespace tk
{
Application::Application()
{
    // Initialize logging system
    Log::init();

    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE)
        throw Exception("Unable to initialize GLFW");

    glfwSetErrorCallback(glfw_error_callback);

    LOG_INFO("Application started");
}

Application::~Application()
{
    LOG_INFO("Application terminating");
    glfwTerminate();
}

// public:

WindowUID Application::createWindow(unsigned width, unsigned height, const std::string &title)
{
    return 0;
}
// private:

// callbacks:

void glfw_error_callback(int error_code, const char *description)
{
    throw GLFWException(description, error_code);
}
} // namespace tk