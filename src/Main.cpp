#include "pch.h"

#include <application/Application.h>
#include <application/Window.h>
#include <system/Log.h>
#include <system/exception/Exception.h>

#include <maths/Maths.h>

#include <iostream>

int main(int argc, char* argv[])
{
    try {
        tk::Application& app = tk::Application::getInstance();
        tk::WindowUID mainWindow = app.createWindow(1280, 720, "TESTLIAS");

        tk::Window* w = app.getInternalWindow(mainWindow);

        w->setIcon("res/icon.png");
        w->useMouseAsInput(false);

        app.runLoop();
    } catch (tk::Exception& e) {
        std::cout << "------ Stopping on exception ------\n"
                  << e.what() << std::endl;
        return -1;  // Or re-throw, not sure...
    }
    return 0;
}