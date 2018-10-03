#pragma once
#ifndef _PARALLAX_UTILS_LOG_H_
#define _PARALLAX_UTILS_LOG_H_

#include <map>
#include <vector>

// TODO: Make it platform independent
#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "../StringUtils.h"

namespace prx {
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

	static CONSOLE_COLOR CONSOLE_COLORS[4] = { CONSOLE_COLOR::WHITE,
											   CONSOLE_COLOR::YELLOW,
											   CONSOLE_COLOR::RED,
											   CONSOLE_COLOR::RED };

	class Log {
	private:
		inline static LOG_LEVEL m_Level = LOG_LEVEL::LOG_INFO;
		inline static HANDLE	m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		//inline static std::map<LOG_LEVEL, std::vector<std::string>> m_LogBuffer;

	public:
		Log() = delete;
		template<typename... Args>
		inline static void message(LOG_LEVEL level, Args... args);
		inline static void setLevel(LOG_LEVEL level) {};

	private:

		template<typename Arg>
		inline static void messageInternal(LOG_LEVEL level, Arg&& arg);

		template<typename First, typename... Args>
		inline static void messageInternal(LOG_LEVEL level, First&& first, Args&&... arg);

		template<typename T>
		inline static void print(LOG_LEVEL level, const T& msg);

		inline static void printNewLine();

		inline static void printLevel(LOG_LEVEL level);

	};

	inline void Log::printNewLine() {
		std::cout << std::endl;
	}

	inline void Log::printLevel(LOG_LEVEL level) {
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(CONSOLE_COLORS[static_cast<int>(level)]));
		std::cout << "[";
		//std::cout << std::setw(13);
		std::cout.setf(std::ios::left);
		std::cout << "PARALLAX";
		std::cout.unsetf(std::ios::left);
		std::cout << "] ";
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(CONSOLE_COLOR::WHITE));
	}

	template <typename ... Args>
	void Log::message(LOG_LEVEL level, Args... args) {
		printLevel(level);
		messageInternal(level, std::forward<Args>(args)...);
	}

	template <typename Arg>
	void Log::messageInternal(LOG_LEVEL level, Arg&& arg) {
		//m_LogBuffer[level].emplace_back(utils::StringUtils::toString(std::forward<Arg>(arg)...));
		if (level >= m_Level) {
			print(level, std::forward<Arg>(arg));
			printNewLine();
		}
	}

	template <typename First, typename... Args>
	void Log::messageInternal(LOG_LEVEL level, First&& first, Args&&... args) {
		//m_LogBuffer[level].emplace_back(utils::StringUtils::toString(std::forward<Args>(args)...));
		if (level >= m_Level)
			print(level, std::forward<First>(first));
		messageInternal(level, std::forward<Args>(args)...);
	}

	template<typename T>
	void Log::print(LOG_LEVEL level, const T& msg) {
		std::cout << utils::StringUtils::toString(msg);
	}
}
#endif
