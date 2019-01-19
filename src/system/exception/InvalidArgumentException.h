#pragma once
#include "Exception.h"

#include <iomanip>  // Conversion of the error code to hex
#include <string>

namespace tk {
class InvalidArgumentException : public Exception
{
  public:
    explicit InvalidArgumentException(const char* message)
        : Exception(message)
    {
    }

    explicit InvalidArgumentException(const std::string& message)
        : Exception(message)
    {
    }

    virtual ~InvalidArgumentException() noexcept
    {
    }
};
}  // namespace tk