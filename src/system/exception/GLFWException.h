#pragma once
#include "Exception.h"

#include <string>

namespace tk
{
class GLFWException : public Exception
{
public:
  explicit GLFWException(const char *message, int error_code)
      : Exception(message)
  {
    m_msg = "GLFW error occured (code: ";
    m_msg += std::to_string(error_code);
    m_msg += "):\n  " + std::string(message);
  }

  explicit GLFWException(const std::string &message, int error_code)
      : GLFWException(message.c_str(), error_code) // Delegated constructor
  {
  }

  virtual ~GLFWException() noexcept
  {
  }
};
} // namespace tk