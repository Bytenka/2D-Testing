#pragma once

#include <Main.h>

#ifdef TK_DEBUG
#    define glCheck(func)                                \
        do {                                             \
            func;                                        \
            checkOpenGLError(#func, __FILE__, __LINE__); \
        } while (false)
#else
#    define glCheck(func) func
#endif

namespace tk {
void checkOpenGLError(const char* expr, const char* file_name, unsigned line);
}  // namespace tk