#pragma once

#include "core.hpp"
#include <spdlog/spdlog.h>

namespace Citrus {
    class CITRUS_API Log {
        inline static std::shared_ptr<spdlog::logger> s_coreLogger;
        inline static std::shared_ptr<spdlog::logger> s_clientLogger;

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; };
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; };
    };
}

#define CITRUS_CORE_TRACE(...)::Citrus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CITRUS_CORE_INFO(...)::Citrus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CITRUS_CORE_WARN(...)::Citrus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CITRUS_CORE_ERROR(...)::Citrus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CITRUS_CORE_FATAL(...)::Citrus::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CITRUS_TRACE(...)::Citrus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CITRUS_INFO(...)::Citrus::Log::GetClientLogger()->info(__VA_ARGS__)
#define CITRUS_WARN(...)::Citrus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CITRUS_ERROR(...)::Citrus::Log::GetClientLogger()->error(__VA_ARGS__)
#define CITRUS_FATAL(...)::Citrus::Log::GetClientLogger()->fatal(__VA_ARGS__)