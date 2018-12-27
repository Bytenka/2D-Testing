#include "pch.h"

#include <system/Log.h>
#include <system/exception/Exception.h>
#include <application/Application.h>
#include <application/Window.h>

#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        tk::Application &app = tk::Application::getInstance();

        tk::WindowUID mainWindow = app.createWindow(1280, 720, "TESTLIAS");

        tk::Window w(1280, 720, "TESTLIAS");
        w.setIcon("res/icon.png");
    }
    catch (tk::Exception &e)
    {
        std::cout << "------ Stopping on exception ------\n"
                  << e.what() << std::endl;
        return -1;
    }
    return 0;
}