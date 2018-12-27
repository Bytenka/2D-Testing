#include "Window.h"

#include <system/exception/Exception.h>
#include <system/Log.h>
#include <graphics/Image.h>

namespace tk
{
Window::Window(unsigned width, unsigned height, const std::string &title)
    : m_title(title), m_width(width), m_height(height), m_cursorPos({width / 2, height / 2})
{
    // Window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *newWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (newWindow == NULL)
        throw Exception("Unable to create window");

    glfwMakeContextCurrent(newWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw Exception("GLAD loader failed");

    glfwSwapInterval(1);
    //glfwSetFramebufferSizeCallback(newWindow, framebuffer_size_callback);
    // @TODO glfwSetWindowFocusCallback()

    // Setting up OpenGL. Functions are safe to call in that configuration
    glCheck(glViewport(0, 0, width, height));
    glCheck(glEnable(GL_DEPTH_TEST));
    glCheck(glEnable(GL_CULL_FACE));
    glCheck(glFrontFace(GL_CCW));
    glCheck(glCullFace(GL_BACK));

    // Transparency
    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_glfwWindow = newWindow;
    setClearColor(0, 127, 127);

    useMouseAsInput(true);

    glfwMakeContextCurrent(NULL);

    LOG_INFO("Created new window \"{}\" ({}, {})", m_title, m_width, m_height);
}

Window::~Window()
{
    LOG_INFO("Destroying window \"{}\"", m_title);
    glfwDestroyWindow(m_glfwWindow);
}

// public:

void Window::update() noexcept
{
    glfwPollEvents();

    m_cursorTravel = glm::dvec2(0);
    if (m_mouseIsInput)
    {
        glfwGetCursorPos(m_glfwWindow, &m_cursorTravel.x, &m_cursorTravel.y);
        glfwSetCursorPos(m_glfwWindow, 0, 0); // Because GLFW won't do it for us...
    }
}

void Window::setClearColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const noexcept
{
    glCheck(glClearColor(
        red / 255.0f,
        green / 255.0f,
        blue / 255.0f,
        alpha / 255.0f));
}

void Window::setIcon(const std::string &imgPath)
{
    try
    {
        Image img(imgPath);

        GLFWimage glfwImage;
        glfwImage.width = img.getWidth();
        glfwImage.height = img.getHeight();
        glfwImage.pixels = img.getData();

        glfwSetWindowIcon(m_glfwWindow, 1, &glfwImage);
    }
    catch (Exception &e)
    {
        LOG_ERROR("Unable to set icon for window \"{}\": {}", m_title, e.what());
    }
}

void Window::updateSize(int width, int height) noexcept
{
    m_width = width;
    m_height = height;
    glCheck(glViewport(0, 0, width, height));
}

void Window::useMouseAsInput(bool value) noexcept
{
    if (value)
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //updateCursorPosition(m_width / 2.0, m_height / 2.0);
    }
    else
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    m_mouseIsInput = value;
}

// callbacks:
void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept
{
    //if (width != 0 && height != 0)
    //    Application::getInstance().updateWindowSize(window, width, height);
}
} // namespace tk
