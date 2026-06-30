#include "Logger.h"
#include <chrono>
#include <print>

namespace Bake {
	void Logger::Print(LogLevel level, std::string_view catagory, std::string_view msg) {
		const char* name = "Info";
		switch (level)
		{
		case Bake::LogLevel::Info:
			name = "Info";
			break;
		case Bake::LogLevel::Warn:
			name = "Warn";
			break;
		case Bake::LogLevel::Error:
			name = "Error";
			break;
		case Bake::LogLevel::Critical:
			name = "Critical";
			break;
		}
		const auto now = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
		const auto time = std::chrono::floor<std::chrono::seconds>(now);
		std::println("[{:%H:%M:%S}][{}][{}]: {}", time, catagory, name, msg);
	}
}