//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_LOGGER_HPP
#define MACH_LOGGER_HPP


#include <ostream>
#include <string>

namespace mach {
	enum LogLevel {
		All = 0,
		Debug = 1,
		Info = 2,
		Error = 3,
		Off = 4
	};

	enum LogType {
		LogDebug = 1,
		LogInfo = 2,
		LogError = 3,
	};

	class Logger {
		LogLevel m_level;

		Logger() : m_level(All) {};

		~Logger() = default;

		static void print_log(const std::string &p_prefix, const std::string &p_message);

		static void print_error(const std::string &p_prefix, const std::string &p_message);

		static Logger &get_instance();

	public:
		static void log(const std::string &p_message, LogType p_level = LogInfo);

		static void log(std::stringstream &p_os, LogType p_level);

		static void set_log_level(LogLevel p_level);

		static LogLevel get_log_level();
	};


}


#endif //MACH_LOGGER_HPP
