#pragma once

#ifndef _GLERRORHANDLER_H_
#define _GLERRORHANDLER_H_

#include <iostream>
#include <sstream>

#include <GL/gl3w.h>
#include "../log/Log.h"

// Define PARALLAX_DEBUG to enable debug macros

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef PARALLAX_DEBUG 
	#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else 
	#define GLCall(x) x 
#endif
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::stringstream messageStream;
		messageStream << error << " : " << function << " " << file << " : " << line << std::endl;
		prx::Log::message(prx::LOG_LEVEL::LOG_FATAL, messageStream.str());
		return false;
	}
	return true;
}
#endif
