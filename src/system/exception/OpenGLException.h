#pragma once
#include "Exception.h"

#include <iomanip> // Conversion of the error code to hex
#include <string>

namespace tk
{
class OpenGLException : public Exception
{
public:
  OpenGLException(const char *file, unsigned line, const char *errorName, const char *message)
      : Exception(message), m_inFile(file), m_atLine(line)
  {
    std::stringstream toHex;
    toHex << std::hex << errorName;
    m_errorName = toHex.str();

    m_msg = "OpenGL error occured:\n";
    m_msg += "  In file " + m_inFile;
    m_msg += "\n    At line " + std::to_string(m_atLine);
    m_msg += "\n    Error type: " + m_errorName;
    m_msg += "\n    Description: " + std::string(message);
  }

  virtual ~OpenGLException() noexcept
  {
  }

protected:
  std::string m_errorName;
  std::string m_inFile;
  unsigned m_atLine;
};
} // namespace tk