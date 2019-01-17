#include "pch.h"
#include "GLCheck.h"
#include <system/exception/OpenGLException.h>

#include <glad/glad.h>

#include <string>

namespace tk
{
static std::string errorName;
static std::string msg;

void checkOpenGLError(const char *expr, const char *file_name, unsigned line)
{
    GLenum err;

    if (!errorName.empty())
        errorName.clear();

    if (!msg.empty())
        msg.clear();

    bool gotAnError = false;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        if (gotAnError)
        {
            errorName += ", ";
            msg += " ";
        }

        switch (err)
        {
        case GL_INVALID_ENUM:
        {
            errorName += "GL_INVALID_ENUM";
            msg += "An unacceptable value is specified for an enumerated argument.";
            break;
        }

        case GL_INVALID_VALUE:
        {
            errorName += "GL_INVALID_VALUE";
            msg += "A numeric argument is out of range.";
            break;
        }

        case GL_INVALID_OPERATION:
        {
            errorName += "GL_INVALID_OPERATION";
            msg += "The specified operation is not allowed in the current state.";
            break;
        }

        case GL_INVALID_FRAMEBUFFER_OPERATION:
        {
            errorName += "GL_INVALID_FRAMEBUFFER_OPERATION";
            msg += "The framebuffer object is not complete.";
            break;
        }

        case GL_OUT_OF_MEMORY:
        {
            errorName += "GL_OUT_OF_MEMORY";
            msg += "There is not enough memory left to execute the command.";
            break;
        }

        default:
            errorName += "UNKNOWN_ERROR";
            msg += "Unhandeled OpenGL error.";
            break;
        }

        gotAnError = true;
    }

    if (gotAnError)
        throw OpenGLException(file_name, line, errorName.c_str(), msg.c_str());
}
} // namespace tk
