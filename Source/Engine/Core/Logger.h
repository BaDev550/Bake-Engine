#pragma once
#include <iostream>
#include <string>
#include <string_view>

namespace Bake {
	enum class LogLevel {
		Info,
		Warn,
		Error,
		Critical
	};

	class Logger final {
	public:
		template<typename... Args>
		static void Info(std::string_view catagory, std::format_string<Args...> fmt, Args&&... args) {
			std::string msg = std::format(fmt, std::forward<Args>(args)...);
			Print(LogLevel::Info, catagory, msg);
		}
		template<typename... Args>
		static void Warn(std::string_view catagory, std::format_string<Args...> fmt, Args&&... args) {
			std::string msg = std::format(fmt, std::forward<Args>(args)...);
			Print(LogLevel::Warn, catagory, msg);
		}
		template<typename... Args>
		static void Error(std::string_view catagory, std::format_string<Args...> fmt, Args&&... args) {
			std::string msg = std::format(fmt, std::forward<Args>(args)...);
			Print(LogLevel::Error, catagory, msg);
		}
		template<typename... Args>
		static void Critical(std::string_view catagory, std::format_string<Args...> fmt, Args&&... args) {
			std::string msg = std::format(fmt, std::forward<Args>(args)...);
			Print(LogLevel::Critical, catagory, msg);
		}
	private:
		static void Print(LogLevel level, std::string_view catagory, std::string_view msg);
	};
}