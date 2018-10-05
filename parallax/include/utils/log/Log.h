#pragma once
#ifndef _PARALLAX_UTILS_LOG_H_
#define _PARALLAX_UTILS_LOG_H_

#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#include <fstream>

// TODO: Make it platform independent
#include <windows.h>

#include "../StringUtils.h"

//------------------------
//	TODO:
//------------------------
// - printDirect method to print direct to the console
// - direct file exporting to export messages in runtime
// - export to file in PRX_FATAL and PRX_ASSERT
// - log destinations

namespace prx {

	enum class LOG_LEVEL {
		LOG_INFO	= 0,
		LOG_WARN	= 1,
		LOG_ERROR	= 2,
		LOG_FATAL	= 3
	};

	enum class LOG_TARGET {
		BUFFER		= 1, 
		CONSOLE		= 1 << 1,
		DEBUG_LAYER = 1 << 2,
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

	static std::array<CONSOLE_COLOR, 4> CONSOLE_COLORS  = { CONSOLE_COLOR::WHITE,
														    CONSOLE_COLOR::YELLOW,
														    CONSOLE_COLOR::RED,
														    CONSOLE_COLOR::RED };

	static std::array<std::string, 4> LOG_LEVEL_STRINGS = { "INFO ",
														    "WARN ",
														    "ERROR",
														    "FATAL" };

	class Log {
	private:
		inline static LOG_LEVEL  m_Level;
		inline static HANDLE	 m_ConsoleHandle;
		// Might be slow
		// TODO: Mb replace it to a raw array
		inline static std::string			  m_MessageBuffer;
		inline static std::vector<LogMessage> m_LogBuffer;

		inline static std::ostream& m_DefaultStream = std::cout;

	public:
		Log() = delete;

		static void init();

		template<typename... Args>
		inline static void message(LOG_LEVEL level, Args&&... args);
		
		inline static void setLevel(LOG_LEVEL level);

		inline static void exportToFile(LOG_LEVEL level, std::string_view path);
		
	private:

		inline static void printBuffer(std::ostream& stream, LOG_LEVEL level, 
									   CONSOLE_COLOR color = CONSOLE_COLOR::WHITE);

		template<typename T>
		inline static void pushToBuffer(const T& msg);

		inline static void pushNewLineToBuffer();

		inline static void printLevel(std::ostream& stream, LOG_LEVEL level);

		template<typename Arg>
		inline static void handleMessage(Arg&& arg);
		
		template<typename First, typename... Args>
		inline static void handleMessage(First&& first, Args&&... args);
	};

#ifndef PARALLAX_DISABLE_LOG

#define PRX_INFO(...) prx::Log::message(prx::LOG_LEVEL::LOG_INFO, __VA_ARGS__)

#define PRX_WARN(...) prx::Log::message(prx::LOG_LEVEL::LOG_WARN,  __VA_ARGS__, " : ", __FUNCSIG__, "\nFILE:  ", __FILE__, " LINE: ", __LINE__, ")")

#define PRX_ERROR(...) prx::Log::message(prx::LOG_LEVEL::LOG_ERROR, __VA_ARGS__, " : ", __FUNCSIG__, "\nFILE:  ", __FILE__, " LINE: ",  __LINE__, ")")

#define PRX_FATAL(...)		do {\
							prx::Log::message(prx::LOG_LEVEL::LOG_FATAL,	 \
							"\n*********************************\n",		 \
							"\t FATAL ERROR!\n",							 \
							  "*********************************\n",		 \
							__VA_ARGS__, " : ", __FUNCSIG__, "\n",			 \
							"FILE:  ", __FILE__, " LINE: ",  __LINE__, ")"); \
							__debugbreak();									 \
							} while(false)

#define PRX_ASSERT(x, ...)  do {											 \
							if(!x) {										 \
							prx::Log::message(prx::LOG_LEVEL::LOG_FATAL,	 \
							"\n*********************************\n",		 \
							"\t ASSERTION FAILED!\n",						 \
							  "*********************************\n",		 \
							__VA_ARGS__, " : ", __FUNCSIG__, "\n",			 \
							"FILE:  ", __FILE__, " LINE: ",  __LINE__, ")"); \
							__debugbreak();									 \
							} } while(false)
#else	

#define PRX_INFO(...)   do{}while(false)
#define PRX_WARN(...)   do{}while(false)
#define PRX_ERROR(...)  do{}while(false)
#define PRX_FATAL(...)  __debugbreak()
#define PRX_ASSERT(...) __debugbreak()

#endif

	template <typename ... Args>
	void Log::message(LOG_LEVEL level, Args&&... args) {
		if (level >= m_Level) {
			m_MessageBuffer.clear();
			handleMessage(std::forward<Args>(args)...);
			// TODO: add log destination flags
			m_LogBuffer.emplace_back(level, m_MessageBuffer);
			if (level == LOG_LEVEL::LOG_FATAL)
				printBuffer(m_DefaultStream, level, CONSOLE_COLOR::RED);
			else
				printBuffer(m_DefaultStream, level);
		}
	}

	inline void Log::init() {
		m_MessageBuffer.reserve(256);

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
			PRX_ERROR("LOG: Can`t open output logging file: ", path);
			return;
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

	inline void Log::printBuffer(std::ostream& stream, LOG_LEVEL level, CONSOLE_COLOR color) {
		printLevel(stream, level);
		SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(color));
		stream << m_MessageBuffer;
		SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(CONSOLE_COLOR::WHITE));
	}

	template<typename T>
	void Log::pushToBuffer(const T& msg) {
		m_MessageBuffer += utils::StringUtils::toString(msg);
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
