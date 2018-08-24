#include "Log.h"
#include <array>
#include <iostream>
#include <iomanip>
#include <string>


namespace prx {

	const static std::array<std::string, 5> LOG_LEVEL_NAME = {
		" LOG_MESSAGE ",
		"  LOG_DEBUG  ",
		"  LOG_INIT   ",
		" LOG_WARNING ",
		"  LOG_ERROR  "
	};

	static enum class CONSOLE_COLOR {
		WHITE = 15,
		GRAY = 7,
		GREEN = 2,
		YELLOW = 14,
		RED = 12
	};

	const static unsigned int MAX_LOG_LEVEL = LOG_ERROR;
	const static unsigned int MIN_LOG_LEVEL = LOG_DEFAULT;

	const static std::array<CONSOLE_COLOR, 5> LOG_LEVEL_COLOR = {
		CONSOLE_COLOR::WHITE,
		CONSOLE_COLOR::GRAY,
		CONSOLE_COLOR::GREEN,
		CONSOLE_COLOR::YELLOW,
		CONSOLE_COLOR::RED
	};

	std::map<unsigned int, std::vector<std::string>> Log::m_LogBuffer = std::map<unsigned int, std::vector<std::string>>();
	LOG_LEVEL Log::m_Level = LOG_DEFAULT;
	HANDLE Log::m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	void Log::message(std::string_view message, const LOG_LEVEL level) {
		Log::m_LogBuffer[level].push_back(static_cast<std::string>(message));
		if (level >= Log::m_Level)
			printMessage(message, level);
	}

	void Log::printMessage(std::string_view message, const LOG_LEVEL level) {
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(LOG_LEVEL_COLOR[level]));
		std::cout << "[";
		std::cout << std::setw(13);
		std::cout.setf(std::ios::left);
		std::cout << LOG_LEVEL_NAME[level];
		std::cout.unsetf(std::ios::left);
		std::cout << "] ";
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(CONSOLE_COLOR::WHITE));
		std::cout << message << std::endl;
	}

	void Log::setLevel(const LOG_LEVEL level) {
		m_Level = level;
	}

	void Log::printBuffer() {
		for (int i = MIN_LOG_LEVEL; i <= MAX_LOG_LEVEL; i++)
			for (auto& element : m_LogBuffer[i]) {
				printMessage(element, static_cast<LOG_LEVEL>(i));
			}
	}

	void Log::printBufferLevel(const LOG_LEVEL level) {
		for (auto& element : m_LogBuffer[level]) {
			printMessage(element, static_cast<LOG_LEVEL>(level));
		}
	}

	void Log::clearBuffer() {
		for (int i = MIN_LOG_LEVEL; i <= MAX_LOG_LEVEL; i++) {
			m_LogBuffer[i].clear();
			m_LogBuffer[i].shrink_to_fit();
		}
	}

	void Log::clearBufferLevel(const LOG_LEVEL level) {
		m_LogBuffer[level].clear();
		m_LogBuffer[level].shrink_to_fit();
	}
}
