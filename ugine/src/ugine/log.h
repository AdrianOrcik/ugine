#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <fstream>

// todo: add more specific macros
// todo: implement realtime logging errors into files
namespace Ugine
{
	class UE_API Log
	{
	public:
		Log();
		~Log();
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreExportLogger() { return core_export_logger_; }
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger_; }

		inline static std::shared_ptr<spdlog::logger>& GetClientExportLogger() { return client_export_logger_; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_export_logger_;
		static std::shared_ptr<spdlog::logger> core_logger_;

		static std::shared_ptr<spdlog::logger> client_export_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// core log macros
#define CORE_LOG_TRACE(...){ ::Ugine::Log::GetCoreLogger()->trace(__VA_ARGS__);			\
							 ::Ugine::Log::GetCoreExportLogger()->trace(__VA_ARGS__);	\
}

#define CORE_LOG_INFO(...){	 ::Ugine::Log::GetCoreLogger()->info(__VA_ARGS__);			\
							 ::Ugine::Log::GetCoreExportLogger()->info(__VA_ARGS__);	\
}

#define CORE_LOG_WARN(...){	::Ugine::Log::GetCoreLogger()->warn(__VA_ARGS__);		\
							::Ugine::Log::GetCoreExportLogger()->warn(__VA_ARGS__);	\
}

#define CORE_LOG_ERROR(...){	::Ugine::Log::GetCoreLogger()->error(__VA_ARGS__);		\
								::Ugine::Log::GetCoreExportLogger()->error(__VA_ARGS__);	\
}


// client log macros
#define LOG_TRACE(...){ ::Ugine::Log::GetClientLogger()->trace(__VA_ARGS__);			\
						 ::Ugine::Log::GetClientExportLogger()->trace(__VA_ARGS__);	\
}

#define LOG_INFO(...){	 ::Ugine::Log::GetClientLogger()->info(__VA_ARGS__);			\
						 ::Ugine::Log::GetClientExportLogger()->info(__VA_ARGS__);	\
}

#define LOG_WARN(...){	::Ugine::Log::GetClientLogger()->warn(__VA_ARGS__);		\
						::Ugine::Log::GetClientExportLogger()->warn(__VA_ARGS__);	\
}

#define LOG_ERROR(...){	::Ugine::Log::GetClientLogger()->error(__VA_ARGS__);		\
						::Ugine::Log::GetClientExportLogger()->error(__VA_ARGS__);	\
}
