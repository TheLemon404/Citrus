#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Citrus {
    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_coreLogger = spdlog::stdout_color_mt("CITRUS");
        s_coreLogger->set_level(spdlog::level::trace);

        s_clientLogger = spdlog::stdout_color_mt("CLIENT");
        s_clientLogger->set_level(spdlog::level::trace);

        CITRUS_CORE_INFO("core logger initialized");
        CITRUS_INFO("client logger initialized");
    }
}