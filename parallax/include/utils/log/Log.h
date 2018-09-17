#pragma once
#ifndef _LOG_H_
#define _LOG_H_

#include <map>
#include <vector>
#include <string_view>

// TODO: Make it platform independent
#include <windows.h>

namespace prx {

	enum LOG_LEVEL {
		LOG_DEFAULT = 0,
		LOG_DEBUG = 1,
		LOG_INIT = 2,
		LOG_WARNING = 3,
		LOG_ERROR = 4,
	};

	class Log {
	private:
		Log();
		static LOG_LEVEL m_Level;
		static std::map<unsigned int, std::vector<std::string>> m_LogBuffer;
		// WinAPI stuff to change console text color
		static HANDLE m_consoleHandle;
	public:
		static void message(std::string_view message, const LOG_LEVEL level);
		static void printMessage(std::string_view message, const LOG_LEVEL level);
		static void setLevel(const LOG_LEVEL level);
		static void printBuffer();
		static void printBufferLevel(const LOG_LEVEL level);
		static void clearBuffer();
		static void clearBufferLevel(const LOG_LEVEL level);
	};
}
#endif


