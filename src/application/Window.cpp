#include "pch.h"
#include "Window.h"

#include <system/exception/Exception.h>
#include <system/Log.h>
#include <graphics/GLCheck.h>
#include <graphics/Image.h>

namespace tk {
Window::Window(unsigned width, unsigned height, const std::string& title)
    : m_renderer(this), m_title(title), m_width(width), m_height(height), m_cursorPos({width / 2.0, height / 2.0})
{
    // Window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* newWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (newWindow == NULL)
        throw Exception("Unable to create window");

    glfwMakeContextCurrent(newWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw Exception("GLAD loader failed");

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(newWindow, this);  // Used to get back Window object in callbacks
    glfwSetFramebufferSizeCallback(newWindow, framebuffer_size_callback);
    // @TODO glfwSetWindowFocusCallback()

    // Setting up OpenGL. Context is bound, these are safe to call
    glCheck(glViewport(0, 0, width, height));
    glCheck(glFrontFace(GL_CCW));
    glCheck(glCullFace(GL_BACK));
    glCheck(glEnable(GL_CULL_FACE));
    glCheck(glEnable(GL_DEPTH_TEST));

    // Transparency
    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_glfwWindow = newWindow;
    m_renderer.init();

    glfwMakeContextCurrent(NULL);  // Calls after this should bind and unbind the context

    setClearColor({0, 127, 127});
    useMouseAsInput(true);

    LOG_INFO("Created new window \"{}\" ({}, {})", m_title, m_width, m_height);
}

Window::~Window()
{
    bindContext();
    m_renderer.dispose();
    unbindContext();

    LOG_INFO("Destroying window \"{}\"", m_title);
    glfwDestroyWindow(m_glfwWindow);
}

// public:

void Window::update() noexcept
{
    bindContext();

    glfwPollEvents();

    // Behavior changes depending on the input method.
    // glfwGetCursorPos returns the offset between calls when cursor is disabled,
    // and the real (relative) position of the cursor otherwise
    glfwGetCursorPos(m_glfwWindow, &m_cursorPos.x, &m_cursorPos.y);
    if (m_mouseIsInput)
        glfwSetCursorPos(m_glfwWindow, 0, 0);  // Because GLFW doesn't do it automatically

    unbindContext();
}

void Window::setClearColor(const Color& color) const noexcept
{
    bindContext();

    try {
        auto c = color.normalized();
        glCheck(glClearColor(c.x, c.y, c.z, c.w));
    } catch (Exception& e) {
        LOG_ERROR("Unable to set clear color: {}", e.what());
    }

    unbindContext();
}

void Window::setIcon(const std::string& imgPath) noexcept
{
    try {
        Image img(imgPath);

        GLFWimage glfwImage;
        glfwImage.width = img.getWidth();
        glfwImage.height = img.getHeight();
        glfwImage.pixels = img.getData();

        glfwSetWindowIcon(m_glfwWindow, 1, &glfwImage);
    } catch (Exception& e) {
        LOG_ERROR("Unable to set icon for window \"{}\": {}", m_title, e.what());
    }
}

void Window::updateSize(int width, int height) noexcept
{
    bindContext();

    m_width = width;
    m_height = height;

    try {
        glCheck(glViewport(0, 0, width, height));
    } catch (Exception& e) {
        LOG_ERROR("Could not resize window correctly: {}", e.what());
    }

    unbindContext();
}

void Window::useMouseAsInput(bool value) noexcept
{
    if (value)
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    else
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    m_mouseIsInput = value;
}

void Window::display()
{
    bindContext();

    m_renderer.drawNewFrame();
    glfwSwapBuffers(m_glfwWindow);

    unbindContext();
}

void Window::clear() const
{
    bindContext();

    glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    unbindContext();
}

// callbacks:
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept
{
    if (width != 0 && height != 0)
        ((Window*)glfwGetWindowUserPointer(window))->updateSize(width, height);
}
}  // namespace tk
