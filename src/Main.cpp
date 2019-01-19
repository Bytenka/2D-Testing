#include "pch.h"

#include <application/Application.h>
#include <application/Window.h>
#include <system/exception/Exception.h>

#include <iostream>

#include <graphics/Mesh.h>

#include <system/Log.h>

#include <graphics/Vertex.h>

int main(int argc, char* argv[])
{
    try {
        tk::Application& app = tk::Application::getInstance();
        tk::WindowUID mainWindow = app.createWindow(1280, 720, "TESTLIAS");

        tk::Window* w = app.getInternalWindow(mainWindow);

        w->setIcon("res/icon.png");
        w->useMouseAsInput(false);

        tk::Mesh m;
        m.addVertex({{100.0f, 100.0f, 100.0f}});

		for (auto& a : m.getData())
            std::cout << a << ", ";

        app.runLoop();
    } catch (tk::Exception& e) {
        std::cout << "------ Stopping on exception ------\n"
                  << e.what() << std::endl;
        return -1;  // Or re-throw, not sure...
    }
    return 0;
}