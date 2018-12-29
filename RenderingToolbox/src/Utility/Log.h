#pragma once
#include "spdlog/spdlog.h"
#include <memory>

class Log {
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clientLogger;
	

};

#define LOG_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)