// ReSharper disable CppInconsistentNaming
#pragma once

#include "spdlog/logger.h"

namespace Serum2D {
    class Log {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    };
}

#define S2D_CORE_TRACE(...)    ::Serum2D::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define S2D_CORE_INFO(...)     ::Serum2D::Log::GetCoreLogger()->info(__VA_ARGS__)
#define S2D_CORE_WARN(...)     ::Serum2D::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define S2D_CORE_ERROR(...)    ::Serum2D::Log::GetCoreLogger()->error(__VA_ARGS__)
#define S2D_CORE_CRITICAL(...) ::Serum2D::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define S2D_TRACE(...)         ::Serum2D::Log::GetClientLogger()->trace(__VA_ARGS__)
#define S2D_INFO(...)          ::Serum2D::Log::GetClientLogger()->info(__VA_ARGS__)
#define S2D_WARN(...)          ::Serum2D::Log::GetClientLogger()->warn(__VA_ARGS__)
#define S2D_ERROR(...)         ::Serum2D::Log::GetClientLogger()->error(__VA_ARGS__)
#define S2D_CRITICAL(...)      ::Serum2D::Log::GetClientLogger()->critical(__VA_ARGS__)