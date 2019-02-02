#include "pch.h"
#include "Log.h"

#include "exception/Exception.h"

#include <Main.h>

#include <iostream>
#include <cstdlib>

namespace tk {
std::shared_ptr<spdlog::logger> Log::s_mainLogger;
bool Log::s_isInitialized = false;

void Log::init() noexcept
{
    if (s_isInitialized)
        LOG_WARN("Log::init() called, but logger is already initialized. Ignoring");

    else {
        try {
            s_mainLogger = spdlog::stdout_color_mt("console");

#ifdef TK_DEBUG
            s_mainLogger->set_level(spdlog::level::trace);
#else
            s_mainLogger->set_level(spdlog::level::info);
#endif
            s_mainLogger->set_pattern("[%T:%e] <%^%l%$> %v");

            s_mainLogger->trace("Initialized logger");
            s_isInitialized = true;
        } catch (const spdlog::spdlog_ex& ex) {
            std::string msg = "FATAL: Log init failed: " + std::string(ex.what());
            std::terminate();  // Because the program need a working logger to report errors
        }
    }
}
}  // namespace tk