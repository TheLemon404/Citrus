#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Citrus {
    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("CITRUS");
        coreLogger->set_level(spdlog::level::trace);

        clientLogger = spdlog::stdout_color_mt("CLIENT");
        clientLogger->set_level(spdlog::level::trace);

        CITRUS_CORE_INFO("core logger initialized");
        CITRUS_INFO("client logger initialized");
    }
}