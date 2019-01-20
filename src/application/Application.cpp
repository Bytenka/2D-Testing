#include "pch.h"
#include "Application.h"

#include "Window.h"

#include <system/Log.h>
#include <system/exception/Exception.h>
#include <system/exception/GLFWException.h>

#include <iostream>
#include <algorithm>


namespace tk {
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
    m_windows.clear();  // Clears everything before calling glfwTerminate();
    glfwTerminate();
}

// public:

void Application::runLoop()
{
    if (m_windows.empty())
        LOG_WARN("No window was created before entering {}. Function will return.", __FUNCTION__);

    while (!m_shouldTerminate) {
        for (int i = m_windows.size() - 1; i >= 0; i--) {
            auto& currentPair = m_windows[i];
            auto& currentWindow = currentPair.second;

            currentWindow->update();
            currentWindow->clear();
            currentWindow->display();

            if (currentWindow->shouldClose()) {
                if (currentPair.first == m_mainWindowUID)
                    m_shouldTerminate = true;

                m_windows.erase(m_windows.begin() + i);
            }
        }
        if (m_windows.empty())
            m_shouldTerminate = true;
    }

	// Remaining windows will be deleted in the destructor
}

WindowUID Application::createWindow(unsigned width, unsigned height, const std::string& title) noexcept
{
    try {
        auto newWindowPtr(std::make_unique<Window>(width, height, title));

        WindowUID uid = m_windowUIDCounter++;
        auto newPair(std::make_pair(uid, std::move(newWindowPtr)));
        m_windows.push_back(std::move(newPair));

        return uid;
    } catch (Exception& e) {
        LOG_ERROR("Cannot create new Window \"{}\": {}", title, e.what());
        return WINDOW_NULL;
    }
}

void Application::destroyWindow(WindowUID uid) noexcept
{
    try {
        if (uid == WINDOW_NULL)
            throw Exception("Window is null");

        if (uid == m_mainWindowUID) {
            LOG_TRACE("Destroying main window -> destroying all windows");
            m_windows.clear();
            m_mainWindowUID = WINDOW_NULL;
            m_windowUIDCounter = 1;
        } else {
            m_windows.erase(getWindowFromUID(uid));
        }
    } catch (Exception& e) {
        LOG_ERROR("Cannot destroy window with UID \"{}\": {}", uid, e.what());
    }
}

Window* Application::getInternalWindow(WindowUID uid) noexcept
{
    try {
        return getWindowFromUID(uid)->second.get();
    } catch (Exception& e) {
        LOG_ERROR("Unable to find window with UID \"{}\": ", uid, e.what());
        return nullptr;
    }
}

// private:

std::vector<std::pair<WindowUID, std::unique_ptr<Window>>>::iterator Application::getWindowFromUID(WindowUID uid)
{
    auto it = std::find_if(
        m_windows.begin(),
        m_windows.end(),
        [&](const std::pair<WindowUID, std::unique_ptr<Window>>& current) {
            return current.first == uid;
        });

    if (it == m_windows.end())
        throw Exception("Unable to find window. Window does not exist");

    return it;
}

std::vector<std::pair<WindowUID, std::unique_ptr<Window>>>::iterator Application::getWindowFromGLFWwindow(GLFWwindow* window)
{
    auto it = std::find_if(
        m_windows.begin(),
        m_windows.end(),
        [&](const std::pair<WindowUID, std::unique_ptr<Window>>& current) {
            return (current.second->getGLFWwindow()) == window;
        });

    if (it == m_windows.end())
        throw Exception("Unable to find GLFW window. Window does not exist");

    return it;
}

// callbacks:

void Application::glfw_error_callback(int error_code, const char* description)
{
    throw GLFWException(description, error_code);
}
}  // namespace tk