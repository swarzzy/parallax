#pragma once
#ifndef _PARALLAX_UTILS_FTERROR_HANDLER_H_
#define _PARALLAX_UTILS_FTERROR_HANDLER_H_

#ifdef PARALLAX_DEBUG 

#include "ErrorHandler.h";

#include <sstream>
#include "../log/Log.h"

#define USE_PARALLAX_FREETYPE_DEBUGGER int ParallaxFreeTypeDebuggerErrorCode; /* 
// Scope sensetive. It`s recommended to declare it all time inside function that uses freetype. */
#define FTCall(x) ParallaxFreeTypeDebuggerErrorCode =  x; ASSERT(FTLogCall(ParallaxFreeTypeDebuggerErrorCode, #x, __FILE__, __LINE__)) 

static bool FTLogCall(int errorCode, const char* function, const char* file, int line) {
	if (errorCode) {
		std::stringstream messageStream;
		messageStream << "FREETYPE: Error:" << " : " << function << " " << file << " : " << line << std::endl;
		prx::Log::message(messageStream.str(), prx::LOG_ERROR);
		return false;
	}
	return true;
}
#else 

#define FTCall(x) x 
#define USE_PARALLAX_FREETYPE_DEBUGGER

#endif
#endif