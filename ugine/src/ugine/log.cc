#include "uepch.h"

#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ugine {

	std::shared_ptr<spdlog::logger> Log::core_logger_;
	std::shared_ptr<spdlog::logger> Log::client_logger_;

	Log::Log()
	{
		Log::core_logger_ = std::shared_ptr<spdlog::logger>();
		Log::client_logger_ = std::shared_ptr<spdlog::logger>();
	}

	Log::~Log()
	{
		delete &core_logger_;
		delete &client_logger_;
	}

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		core_logger_ = spdlog::stderr_color_mt("CORE");
		core_logger_->set_level(spdlog::level::trace);

		client_logger_ = spdlog::stderr_color_mt("APP");
		client_logger_->set_level(spdlog::level::trace);
	}

}