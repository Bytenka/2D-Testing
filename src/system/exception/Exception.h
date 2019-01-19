/*
 * Standard exception class to report error through the program
 * Every other exception must inherit from this class
 */

#pragma once

#include <exception>
#include <string>

namespace tk {
class Exception : public std::exception
{
  public:
    explicit Exception(const char* message) : m_msg(message)
    {
    }

    explicit Exception(const std::string& message) : m_msg(message)
    {
    }

    virtual ~Exception() noexcept
    {
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }

  protected:
    std::string m_msg;
};
}  // namespace tk