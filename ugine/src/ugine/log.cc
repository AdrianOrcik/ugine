#include "uepch.h"

#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Ugine {

	std::shared_ptr<spdlog::logger> Log::core_logger_;
	std::shared_ptr<spdlog::logger> Log::core_export_logger_;

	std::shared_ptr<spdlog::logger> Log::client_logger_;
	std::shared_ptr<spdlog::logger> Log::client_export_logger_;

	Log::Log()
	{
		Log::core_logger_ = std::shared_ptr<spdlog::logger>();
		Log::core_export_logger_ = std::shared_ptr<spdlog::logger>();

		Log::client_logger_ = std::shared_ptr<spdlog::logger>();
		Log::client_export_logger_ = std::shared_ptr<spdlog::logger>();
	}

	Log::~Log()
	{
		delete &core_logger_;
		delete &client_logger_;
		delete &core_export_logger_;
		delete &client_export_logger_;
	}

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		core_export_logger_ = spdlog::basic_logger_mt("CORE_LOG", "logs/core_logs.txt");
		core_export_logger_->set_level(spdlog::level::trace);
		core_export_logger_->trace("START_SESSION------------------------");

		core_logger_ = spdlog::stderr_color_mt("CORE");
		core_logger_->set_level(spdlog::level::trace);

		client_export_logger_ = spdlog::basic_logger_mt("APP_LOG", "logs/app_logs.txt");
		client_export_logger_->set_level(spdlog::level::trace);
		client_export_logger_->trace("START_SESSION------------------------");

		client_logger_ = spdlog::stderr_color_mt("APP");
		client_logger_->set_level(spdlog::level::trace);

	}
}