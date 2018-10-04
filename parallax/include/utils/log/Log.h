#pragma once
#ifndef _PARALLAX_UTILS_LOG_H_
#define _PARALLAX_UTILS_LOG_H_

#include <map>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <typeinfo>

// TODO: Make it platform independent
#include <windows.h>

#include "../StringUtils.h"
#include <typeindex>

//------------------------
//	TODO:
//------------------------
// - printDirect method to print direct to the console
// - direct file exporting to export messages in runtime
// - rework type checking system
// - colors in messages

namespace prx {

	static const unsigned int  LOG_SUPPORTRED_TYPES_COUNT = 8;

	enum class LOG_LEVEL {
		LOG_INFO	= 0,
		LOG_WARN	= 1,
		LOG_ERROR	= 2,
		LOG_FATAL	= 3
	};

	enum class CONSOLE_COLOR {
		WHITE	= 15,
		GRAY	= 7,
		GREEN	= 2,
		YELLOW	= 14,
		RED		= 12
	};

	struct LogMessage {
		LOG_LEVEL	m_Level;
		std::string m_Message;

		LogMessage(LOG_LEVEL level, std::string_view message)
			: m_Level(level), m_Message(message) {};
	};

	static std::array<CONSOLE_COLOR, 4> CONSOLE_COLORS  = { CONSOLE_COLOR::GREEN,
														    CONSOLE_COLOR::YELLOW,
														    CONSOLE_COLOR::RED,
														    CONSOLE_COLOR::RED };

	static std::array<std::string, 4> LOG_LEVEL_STRINGS = { "INFO ",
														    "WARN ",
														    "ERROR",
														    "FATAL" };

	class Log {
	private:
		static LOG_LEVEL m_Level;
		static HANDLE	 m_ConsoleHandle;
		// Might be slow
		// TODO: Mb replace it to a raw array
		inline static std::string			  m_MessageBuffer;
		inline static std::vector<LogMessage> m_LogBuffer;

		inline static std::ostream& m_DefaultStream = std::cout;
		inline static std::vector<std::type_index> m_LoggableTypes;

	public:
		Log() = delete;

		static void init();

		template<typename... Args>
		inline static void message(LOG_LEVEL level, Args&&... args);
		
		inline static void setLevel(LOG_LEVEL level);

		inline static void exportToFile(LOG_LEVEL level, std::string_view path);

		template<typename T>
		static bool isLoggableType(T);

		//inline static void print()

	private:

		inline static void printBuffer(std::ostream& stream, LOG_LEVEL level);

		template<typename T>
		inline static void pushToBuffer(const T& msg);

		inline static void pushNewLineToBuffer();

		inline static void printLevel(std::ostream& stream, LOG_LEVEL level);

		template<typename Arg>
		inline static void handleMessage(Arg&& arg);
		
		template<typename First, typename... Args>
		inline static void handleMessage(First&& first, Args&&... arg);

	};

	template <typename ... Args>
	void Log::message(LOG_LEVEL level, Args&&... args) {
		if (level >= m_Level) {
			m_MessageBuffer.clear();
			handleMessage(std::forward<Args>(args)...);
			m_LogBuffer.emplace_back(level, m_MessageBuffer);
			printBuffer(m_DefaultStream, level);
		}
	}

	inline void Log::init() {
		m_LoggableTypes.emplace_back(typeid(std::string));
		m_LoggableTypes.emplace_back(typeid(char*));
		m_LoggableTypes.emplace_back(typeid(const char*));
		m_LoggableTypes.emplace_back(typeid(char));
		m_LoggableTypes.emplace_back(typeid(int));
		m_LoggableTypes.emplace_back(typeid(unsigned int));
		m_LoggableTypes.emplace_back(typeid(double));
		m_LoggableTypes.emplace_back(typeid(float));

		m_MessageBuffer.reserve(128);

		m_Level = LOG_LEVEL::LOG_INFO;
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	inline void Log::setLevel(LOG_LEVEL level) {
		m_Level = level;
	}

	inline void Log::exportToFile(LOG_LEVEL level, std::string_view path) {
		std::ofstream stream;
		stream.open(std::string(path));
		if (!stream.is_open()) {
			// TODO: Error handling
		}
		for (auto& msg : m_LogBuffer) {
			if (msg.m_Level >= m_Level) {
				stream << "[";
				stream << LOG_LEVEL_STRINGS[static_cast<int>(msg.m_Level)];
				stream << "] ";
				stream << msg.m_Message;
			}
		}
		stream.close();
	}

	inline void Log::printBuffer(std::ostream& stream, LOG_LEVEL level) {
		printLevel(stream, level);
		stream << m_MessageBuffer;
	}

	template <typename T>
	bool Log::isLoggableType(T) {
		auto type = std::type_index(typeid(T));
		for (auto& t : m_LoggableTypes)
			if (type == t)
				return true;
		return false;
	}

	template<typename T>
	void Log::pushToBuffer(const T& msg) {
		if (isLoggableType(msg))
			m_MessageBuffer += utils::StringUtils::toString(msg);
		else
			m_MessageBuffer += " <unknown symbol> ";
	}

	inline void Log::pushNewLineToBuffer() {
		m_MessageBuffer += '\n';
	}

	inline void Log::printLevel(std::ostream& stream, LOG_LEVEL level) {
		SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(CONSOLE_COLORS[static_cast<int>(level)]));
		stream << "[";
		stream << LOG_LEVEL_STRINGS[static_cast<int>(level)];
		stream << "] ";
		SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(CONSOLE_COLOR::WHITE));
	}

	template <typename Arg>
	void Log::handleMessage(Arg&& arg) {
		pushToBuffer(std::forward<Arg>(arg));
		pushNewLineToBuffer();
	}
	// Expand args with recursion
	template <typename First, typename... Args>
	void Log::handleMessage(First&& first, Args&&... args) {
		pushToBuffer(std::forward<First>(first));
		handleMessage(std::forward<Args>(args)...);
	}
}
#endif
