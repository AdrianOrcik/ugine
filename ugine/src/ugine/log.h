#ifndef UE_LOG
#define UE_LOG

#include <memory>

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ugine
{
	class UE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger_; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// core log macros
#define CORE_LOG_TRACE(...)	::Ugine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)	::Ugine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)	::Ugine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)	::Ugine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_FATAL(...)	::Ugine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client log macros
#define LOG_TRACE(...)	::Ugine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	::Ugine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	::Ugine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	::Ugine::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)	::Ugine::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif // !UE_LOG
